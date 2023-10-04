//
// Created by youba on 01/10/2023.
//

#include "ObjectManager.hpp"

namespace UnitiNetEngine {

    ObjectManager::ObjectManager(const Json::Value &value) {
        Json::Value elements = value["objects"];

        for (auto & element : elements) {
            const std::string name = element.get("name", "undefined").asString();
            this->_objects[name] = std::make_unique<Object>(element, this->_sendEvent);
        }
    }

    Object &ObjectManager::getObject(const std::string &name) {
        return *this->_objects[name];
    }

    std::map<std::string, std::unique_ptr<Object>> &ObjectManager::getObjects() {
        return this->_objects;
    }

    void ObjectManager::addObject(std::unique_ptr<Object> object) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_objects[object->getName()] = std::move(object);
    }

    void ObjectManager::removeObject(const std::string &name) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_objects.erase(name);
    }

    void ObjectManager::update() {
        for (auto &object : this->_objects) {
            object.second->update();
        }
    }

    sendEventManager &ObjectManager::getSendEvent() {
        return this->_sendEvent;
    }
}