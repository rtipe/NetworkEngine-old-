//
// Created by youba on 01/10/2023.
//

#pragma once

#include <functional>
#include "IUser.hpp"

namespace UnitiNetEngine {
    using createUserFunction = std::function<std::unique_ptr<IUser>(int id)>;
    class UserManager {
        public:
            IUser &getUser(int id);
            void addUser(std::unique_ptr<IUser> user);
            template<typename OBJECT>
            void addUserCreator() {
                this->_creator = [&](int id) -> std::unique_ptr<IUser> {
                    return std::make_unique<OBJECT>(id);
                };
            }
            void createUser(int id);
            const std::vector<std::unique_ptr<IUser>> &getUsers() const;
            std::vector<std::unique_ptr<IUser>> &getUsers();
            void removeUser(int id);
        private:
            std::vector<std::unique_ptr<IUser>> _users;
            createUserFunction _creator = nullptr;
    };
}

