//
// Created by youba on 01/10/2023.
//

#pragma once

#include <json/value.h>
#include "Object.hpp"
#include "Event/sendEventManager.hpp"

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
            void addObjects(const Json::Value &value);
        private:
            std::map<std::string, std::unique_ptr<Object>> _objects;
            std::vector<std::unique_ptr<Object>> _addObjects;
            std::vector<std::string> _deleteObjects;
            std::mutex _mutex;
            sendEventManager _sendEvent;
    };
}

