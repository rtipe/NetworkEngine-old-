//
// Created by youba on 01/10/2023.
//

#include "EventManager.hpp"

#include <utility>

namespace UnitiNetEngine {

    void EventManager::addEventListener(const std::string &name, eventFunction function) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_events[name] = std::move(function);
    }

    void EventManager::removeEventListener(const std::string &name) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_events.erase(name);
    }

    void EventManager::addBroadcastListener(const std::string &name, broadcastFunction function) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_broadcasts[name] = std::move(function);
    }

    void EventManager::removeBroadcastListener(const std::string &name) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_broadcasts.erase(name);
    }

    void EventManager::emitEvent(const std::string &name, IUser &user, const Json::Value &value) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_events[name](user, value);
    }

    void EventManager::emitBroadcast(const std::string &name, const Json::Value &value) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_broadcasts[name](value);
    }

    const std::map<std::string, eventFunction> &EventManager::getEvents() const {
        return this->_events;
    }

    std::map<std::string, eventFunction> &EventManager::getEvents() {
        return this->_events;
    }

    const std::map<std::string, broadcastFunction> &EventManager::getBroadcasts() const {
        return this->_broadcasts;
    }

    std::map<std::string, broadcastFunction> &EventManager::getBroadcasts() {
        return this->_broadcasts;
    }
}
