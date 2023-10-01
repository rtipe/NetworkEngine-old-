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
        while (true) {
            std::string buffer;
            boost::asio::ip::udp::endpoint senderEndPoint;
            this->_socketUDP.async_receive_from(boost::asio::buffer(buffer), senderEndPoint,
            [&] (const boost::system::error_code &error, std::size_t length) {
                try {
                    Json::Value command;
                    std::istringstream(buffer) >> command;
                } catch (Json::Exception &e) {
                    std::cout << "error inside message" << std::endl;
                    std::cout << e.what() << std::endl;
                }
            });
        }
    }

    Uniti::Uniti(const std::string &projectPath):
    _projectInfo(projectPath),
    _socketUDP(this->_ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), this->_projectInfo.portUDP)) {
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