//
// Created by youba on 01/10/2023.
//

#pragma once

#include <json/value.h>
#include "Object/Transform/Transform.hpp"
#include "Script/ScriptManager.hpp"

namespace UnitiNetEngine {
    class Object {
        public:
            Object(const std::string &name, sendEventManager &eventManager);
            Object(const Json::Value &value, sendEventManager &eventManager);
            void setEnable(bool value);
            const std::string &getName() const;
            bool isEnable() const;
            const Transform &getTransform() const;
            Transform &getTransform();
            const ScriptManager &getScriptManager() const;
            ScriptManager &getScriptManager();
            void update();
            sendEventManager &getsendEvent();
        private:
            Transform _transform;
            bool _isEnable = true;
            std::mutex _mutex;
            std::string _name;
            ScriptManager _scriptManager;
            sendEventManager &_sendEventManager;
    };
}
