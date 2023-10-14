//
// Created by youba on 13/10/2023.
//

#include <iostream>
#include "VesselAlly.hpp"
#include "Uniti.hpp"

void VesselAlly::start() {}

void VesselAlly::update() {
    this->sendPosition({});
    this->checkCollisionWithMissile();
}

void VesselAlly::awake(const Json::Value &value) {
    this->_data = value;
}

VesselAlly::VesselAlly(UnitiNetEngine::Object &object, Entity::Type type, float life, float speed, Entity::Box box)
: Entity(object, type, life, speed, box) {}

void VesselAlly::createVesselAlly(const UnitiNetEngine::IUser &user) {
    auto object = std::make_unique<UnitiNetEngine::Object>(user.getUserInfo().asString(), UnitiNetEngine::Uniti::getInstance().getObjectManager().getSendEvent());
    object->getScriptManager().addScript("VesselAlly", std::make_unique<VesselAlly>(*object, ALLY, 100, 200, Box(0, 0, 32, 16)));
    object->getScriptManager().getScript("VesselAlly").awake(user.getUserInfo());
    object->getScriptManager().start();
    UnitiNetEngine::Uniti::getInstance().getObjectManager().addObject(std::move(object));
}

UnitiNetEngine::Clock &VesselAlly::getClock() {
    return this->_clock;
}
