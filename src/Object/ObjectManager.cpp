//
// Created by youba on 01/10/2023.
//

#include "ObjectManager.hpp"

namespace UnitiNetEngine {

    ObjectManager::ObjectManager(const Json::Value &value) {
        Json::Value elements = value["objects"];

        for (auto & element : elements) {
            const std::string name = element.get("name", "undefined").asString();
            this->_objects[name] = std::make_unique<Object>(element);
        }
    }

    Object &ObjectManager::getObject(const std::string &name) {
        return *this->_objects[name];
    }

    std::map<std::string, std::unique_ptr<Object>> &ObjectManager::getObjects() {
        return this->_objects;
    }

    void ObjectManager::addObject(std::unique_ptr<Object> object) {
        this->_objects[object->getName()] = std::move(object);
    }

    void ObjectManager::removeObject(const std::string &name) {
        this->_objects.erase(name);
    }

    void ObjectManager::update() {
        for (auto &object : this->_objects) {
            object.second->update();
        }
    }
}