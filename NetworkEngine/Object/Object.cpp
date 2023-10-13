//
// Created by youba on 01/10/2023.
//

#include "Object.hpp"
#include "Uniti.hpp"

namespace UnitiNetEngine {
    Object::Object(const std::string &name, sendEventManager &eventManager):
    _sendEventManager(eventManager),
    _transform(*this) {
        this->_name = name;
    }

    Object::Object(const Json::Value &value, sendEventManager &eventManager):
    _sendEventManager(eventManager),
    _transform(*this) {
        const Json::Value& position = value["position"];
        const Json::Value& scale = value["scale"];
        const Json::Value& scripts = value["scripts"];

        this->_name = value.get("name", "").asString();
        this->_transform.getPosition().setX(position.get("x", 0).asFloat());
        this->_transform.getPosition().setY(position.get("y", 0).asFloat());
        this->_transform.getPosition().setZ(position.get("z", 0).asFloat());
        this->_transform.getRotation().setValue(value.get("rotation", 0).asFloat());
        this->_transform.getScale().setX(scale.get("x", 0).asFloat());
        this->_transform.getScale().setY(scale.get("y", 0).asFloat());
        for (const auto & script : scripts) {
            auto name = script["name"].asString();
            this->_scriptManager.addScript(name, Uniti::getInstance().getScriptFactory().createScript(name, *this));
            this->_scriptManager.getScript(name).awake(script);
        }
        this->_scriptManager.start();
    }

    void Object::setEnable(bool value) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_isEnable = value;
    }

    bool Object::isEnable() const {
        return this->_isEnable;
    }

    const Transform &Object::getTransform() const {
        return this->_transform;
    }

    Transform &Object::getTransform() {
        return this->_transform;
    }

    void Object::update() {
        this->_scriptManager.update();
    }

    ScriptManager &Object::getScriptManager() {
        return this->_scriptManager;
    }

    const ScriptManager &Object::getScriptManager() const {
        return this->_scriptManager;
    }

    const std::string &Object::getName() const {
        return this->_name;
    }

    sendEventManager &Object::getsendEvent() {
        return this->_sendEventManager;
    }
}