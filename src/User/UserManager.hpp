//
// Created by youba on 01/10/2023.
//

#pragma once

#include <functional>
#include "IUser.hpp"

namespace UnitiNetEngine {
    using createUserFunction = std::function<std::unique_ptr<IUser>(const Json::Value &value, const boost::asio::ip::udp::endpoint &endpoint)>;
    class UserManager {
        public:
            IUser &getUser(size_t id);
            bool isUserExist(size_t id) const;
            bool isUserExist(const Json::Value &value) const;
            IUser &getUser(const Json::Value &user);
            void addUser(std::unique_ptr<IUser> user);
            template<typename OBJECT>
            void addUserCreator() {
                this->_creator = [&](const Json::Value &value, const boost::asio::ip::udp::endpoint &endpoint) -> std::unique_ptr<IUser> {
                    return std::make_unique<OBJECT>(value);
                };
            }
            std::unique_ptr<IUser> createUser(const Json::Value &value, const boost::asio::ip::udp::endpoint &endpoint);
            const std::vector<std::unique_ptr<IUser>> &getUsers() const;
            std::vector<std::unique_ptr<IUser>> &getUsers();
            void removeUser(const Json::Value &value);
            std::mutex &getMutex();
            void update();
            std::map<boost::asio::ip::udp::endpoint, Json::Value> getPacketToSend();
        private:
            std::mutex _mutex;
            std::vector<std::unique_ptr<IUser>> _users;
            createUserFunction _creator = nullptr;
    };
}

