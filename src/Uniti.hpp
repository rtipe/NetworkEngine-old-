//
// Created by youba on 01/10/2023.
//

#pragma once

#include <string>
#include <boost/asio.hpp>
#include "ProjectInfo.hpp"
#include "Event/EventManager.hpp"
#include "Script/ScriptFactory.hpp"
#include "User/UserManager.hpp"

namespace UnitiNetEngine {
    class Uniti {
        public:
            static void init(const std::string &projectPath);
            void start();
            static Uniti &getInstance();
            const ProjectInfo &getProjectInfo() const;
            const EventManager &getEventManager() const;
            EventManager &getEventManager();
            UserManager &getUserManager();
            ObjectManager &getObjectManager();
            ScriptFactory &getScriptFactory();
        private:
            Uniti(const std::string &projectPath);
            void startReceive();
            void sendPackets();
            void receiveBuffer(const std::string &buffer, boost::asio::ip::udp::endpoint &senderEndPoint, const boost::system::error_code &error, std::size_t length);
            static std::unique_ptr<Uniti> _instance;
            ProjectInfo _projectInfo;
            EventManager _eventManager;
            ScriptFactory _scriptFactory;
            ObjectManager _objectManager;
            UserManager _userManager;
            boost::asio::io_service _ioService;
            boost::asio::ip::udp::socket _socketUDP;
    };
}
