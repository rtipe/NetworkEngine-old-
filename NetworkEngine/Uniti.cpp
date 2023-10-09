//
// Created by youba on 01/10/2023.
//

#include <boost/asio.hpp>
#include <iostream>
#include <sstream>
#include <json/json.h>
#include <thread>
#include "Uniti.hpp"

namespace UnitiNetEngine {

    void Uniti::init(const std::string &projectPath) {
        _instance.reset(new Uniti(projectPath));
    }

    void Uniti::receiveBuffer(const std::string &buffer, boost::asio::ip::udp::endpoint &senderEndPoint) {
        try {
            Json::Value command;
            std::istringstream(buffer) >> command;
            Json::Value userInfo = command["user"];
            Json::Value receivedInfo = command["received"];

            if (!this->_userManager.isUserExist(userInfo))
                this->_userManager.createUser(userInfo, senderEndPoint);
            IUser &user = this->_userManager.getUser(userInfo);

            user.addPacket(command);
            user.checkSentPacket(receivedInfo);
        } catch (std::exception &e) {
            std::cout << "error inside receiveBuffer" << std::endl;
            std::cout << e.what() << std::endl;
        }
    }

    void Uniti::startReceive() {
        this->_socketUDP.async_receive_from(boost::asio::buffer(this->_buffer, this->_size), _senderEndPoint,
        [&] (const boost::system::error_code &error, std::size_t length) {
            if (!error) {
                std::string text(this->_buffer, length);
                auto *packet = new std::tuple<boost::asio::ip::udp::endpoint, std::string>(_senderEndPoint, text);
                this->_queue.push(packet);
            } else {
                //std::cerr << "Error : " << error.message() << std::endl;
            }
            memset(this->_buffer, 0, this->_size);
            this->startReceive();
        });
    }

    void Uniti::sendPackets() {
        if (this->_clock.getMilliSeconds() < this->_projectInfo.latence)
            return;
        this->_clock.restart();
        auto packets = this->_userManager.getPacketToSend();
        for (auto &pair : packets) {
            try {
                Json::FastWriter fastWriter;
                std::string output = fastWriter.write(pair.second);
                this->_socketUDP.send_to(boost::asio::buffer(output), pair.first);
            } catch (std::exception &e) {
                std::cout << "error sent " << e.what() << std::endl;
            }
        }
    }

    void Uniti::start() {
        this->startReceive();
        this->_ioThread = std::thread([](boost::asio::io_context &io_context) {
            io_context.run();
        }, std::ref(this->_ioService));
        while (true) {
            try {
                this->_objectManager.update();
                this->_userManager.update();
                this->sendPackets();
                this->handleReceivePackets();
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
        if (this->_ioThread.joinable())
            this->_ioThread.join();
    }

    void Uniti::handleReceivePackets() {
        this->_queue.consume_all([&](std::tuple<boost::asio::ip::udp::endpoint, std::string> *packet) {
            this->receiveBuffer(std::get<1>(*packet), std::get<0>(*packet));
            delete packet;
        });
    }

    Uniti::Uniti(const std::string &projectPath):
    _projectInfo(projectPath),
    _socketUDP(this->_ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), this->_projectInfo.portUDP)),
    _objectManager(this->_projectInfo.publicScene),
    _queue(10000) {
        boost::asio::ip::address addr = this->_socketUDP.local_endpoint().address();
        std::cout << "ip : " << addr << std::endl;
        std::cout << "port : " << this->_projectInfo.portUDP << std::endl;
    }

    Uniti &Uniti::getInstance() {
        if (!_instance)
            throw std::runtime_error("error");
        return *_instance;
    }

    const ProjectInfo &Uniti::getProjectInfo() const {
        return this->_projectInfo;
    }

    const EventManager &Uniti::getEventManager() const {
        return this->_eventManager;
    }

    EventManager &Uniti::getEventManager() {
        return this->_eventManager;
    }

    ScriptFactory &Uniti::getScriptFactory() {
        return this->_scriptFactory;
    }

    std::unique_ptr<Uniti> Uniti::_instance = nullptr;

    UserManager &Uniti::getUserManager() {
        return this->_userManager;
    }

    ObjectManager &Uniti::getObjectManager() {
        return this->_objectManager;
    }
}