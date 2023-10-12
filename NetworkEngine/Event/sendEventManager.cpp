//
// Created by youba on 04/10/2023.
//

#include "sendEventManager.hpp"

namespace UnitiNetEngine {
    void sendEventManager::addEvent(const std::string &name, const Json::Value &value) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_events[name] = value;
    }

    void sendEventManager::removeEvent(const std::string &name) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_events.erase(name);
    }

    std::map<std::string, Json::Value> &sendEventManager::getEvents() {
        return this->_events;
    }

    void sendEventManager::clear() {
        this->_events.clear();
    }
}