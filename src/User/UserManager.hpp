//
// Created by youba on 01/10/2023.
//

#pragma once

#include <functional>
#include "IUser.hpp"

namespace UnitiNetEngine {
    using createUserFunction = std::function<std::unique_ptr<IUser>(const Json::Value &value)>;
    class UserManager {
        public:
            IUser &getUser(int id);
            bool isUserExist(int id) const;
            bool isUserExist(const Json::Value &user) const;
            IUser &getUser(const Json::Value &user);
            void addUser(std::unique_ptr<IUser> user);
            template<typename OBJECT>
            void addUserCreator() {
                this->_creator = [&](const Json::Value &value) -> std::unique_ptr<IUser> {
                    return std::make_unique<OBJECT>(value);
                };
            }
            void createUser(const Json::Value &value);
            const std::vector<std::unique_ptr<IUser>> &getUsers() const;
            std::vector<std::unique_ptr<IUser>> &getUsers();
            void removeUser(int id);
            std::mutex &getMutex();
            void update();
        private:
            std::mutex _mutex;
            std::vector<std::unique_ptr<IUser>> _users;
            createUserFunction _creator = nullptr;
    };
}

