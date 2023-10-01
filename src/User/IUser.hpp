//
// Created by youba on 01/10/2023.
//

#pragma once

#include <json/value.h>
#include "Object/ObjectManager.hpp"

namespace UnitiNetEngine {
    class IUser {
        public:
            virtual int getId() const = 0;
            virtual void update() = 0;
            virtual void start() = 0;
            virtual void end() = 0;
            virtual void isThisUser(const Json::Value &user) = 0;
            virtual void sendEvent(const std::string &name, const Json::Value &data) = 0;
            virtual ObjectManager &getObjectManager() = 0;
    };
}
