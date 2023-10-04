//
// Created by youba on 01/10/2023.
//

#pragma once

#include <json/value.h>
#include "Object.hpp"

namespace UnitiNetEngine {
    class ObjectManager {
        public:
            ObjectManager(const Json::Value &value);
            Object &getObject(const std::string &name);
            std::map<std::string, std::unique_ptr<Object>> &getObjects();
            void addObject(std::unique_ptr<Object> object);
            void removeObject(const std::string &name);
            void update();
            sendEventManager &getSendEvent();
        private:
            std::map<std::string, std::unique_ptr<Object>> _objects;
            std::mutex _mutex;
            sendEventManager _sendEvent;
    };
}

