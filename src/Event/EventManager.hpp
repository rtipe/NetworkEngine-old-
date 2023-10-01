//
// Created by youba on 01/10/2023.
//

#pragma once

#include <functional>
#include <json/value.h>
#include "User/IUser.hpp"

namespace UnitiNetEngine {
    using eventFunction = std::function<void(IUser &, const Json::Value &)>;
    using broadcastFunction = std::function<void(const Json::Value &)>;
    class EventManager {
        public:
            void addEventListener(const std::string &name, eventFunction function);
            void removeEventListener(const std::string &name);
            void addBroadcastListener(const std::string &name, broadcastFunction function);
            void removeBroadcastListener(const std::string &name);
            void emitEvent(const std::string &name);
            void emitBroadcast(const std::string &name);
            const std::map<std::string, eventFunction> &getEvents() const;
            std::map<std::string, eventFunction> &getEvents();
            const std::map<std::string, broadcastFunction> &getBroadcasts() const;
            std::map<std::string, broadcastFunction> &getBroadcasts();
        private:
            std::map<std::string, eventFunction> _events;
            std::map<std::string, broadcastFunction> _broadcasts;
            std::mutex _mutex;
    };
}

