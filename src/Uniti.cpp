//
// Created by youba on 01/10/2023.
//

#include <boost/asio.hpp>
#include <iostream>
#include <sstream>
#include <json/json.h>
#include "Uniti.hpp"

namespace UnitiNetEngine {

    void Uniti::init(const std::string &projectPath) {
        _instance.reset(new Uniti(projectPath));
    }

    void Uniti::start() {
        std::future<void> async;
        while (true) {
            std::string buffer;
            boost::asio::ip::udp::endpoint senderEndPoint;
            this->_socketUDP.async_receive_from(boost::asio::buffer(buffer), senderEndPoint,
            [&] (const boost::system::error_code &error, std::size_t length) {
                try {
                    Json::Value command;
                    std::istringstream(buffer) >> command;
                    Json::Value userInfo = command["user"];
                    Json::Value receivedInfo = command["received"];

                    if (!this->_userManager.isUserExist(userInfo))
                        this->_userManager.createUser(userInfo);
                    IUser &user = this->_userManager.getUser(userInfo);

                    user.addPacket(command);
                    user.checkSendedPacket(receivedInfo);
                } catch (std::exception &e) {
                    std::cout << "error inside command" << std::endl;
                    std::cout << e.what() << std::endl;
                }
            });
            async = std::async(std::launch::async, [&] () {
                async.wait();
                this->_objectManager.update();
                this->_userManager.update();
            });
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
}