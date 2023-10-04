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

    void Uniti::receiveBuffer(const std::string &buffer, boost::asio::ip::udp::endpoint &senderEndPoint, const boost::system::error_code &error, std::size_t length) {
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
        std::string buffer;
        boost::asio::ip::udp::endpoint senderEndPoint;
        this->_socketUDP.async_receive_from(boost::asio::buffer(buffer), senderEndPoint,
        [&] (const boost::system::error_code &error, std::size_t length) {
            this->receiveBuffer(buffer, senderEndPoint, error, length);
            this->startReceive();
        });
    }

    void Uniti::sendPackets() {
        auto packets = this->_userManager.getPacketToSend();
        for (auto &pair : packets) {
            Json::FastWriter fastWriter;
            std::string output = fastWriter.write(pair.second);
            this->_socketUDP.send_to(boost::asio::buffer(output), pair.first);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(this->_projectInfo.latence));
        this->sendPackets();
    }

    void Uniti::start() {
        this->startReceive();
        std::async(std::launch::async, [&] () {
            this->sendPackets();
        });
        while (true) {
            this->_objectManager.update();
            this->_userManager.update();
        }
    }

    Uniti::Uniti(const std::string &projectPath):
    _projectInfo(projectPath),
    _socketUDP(this->_ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), this->_projectInfo.portUDP)),
    _objectManager(this->_projectInfo.publicScene) {
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