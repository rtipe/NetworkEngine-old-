//
// Created by youba on 04/10/2023.
//

#pragma once

#include <json/value.h>
#include <mutex>

namespace UnitiNetEngine {
    class sendEventManager {
        public:
            void addEvent(const std::string &name, const Json::Value &value);
            void removeEvent(const std::string &name);
            std::map<std::string, Json::Value> &getEvents();
            void clear();
        private:
            std::mutex _mutex;
            std::map<std::string, Json::Value> _events;
    };
}
