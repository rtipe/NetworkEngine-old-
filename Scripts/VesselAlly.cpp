//
// Created by youba on 13/10/2023.
//

#include <iostream>
#include "VesselAlly.hpp"
#include "Uniti.hpp"

void VesselAlly::start() {
    UnitiNetEngine::Uniti::getInstance().getEventManager().addEventListener("vesselMovement", [&] (UnitiNetEngine::IUser &user, const Json::Value &data) {
        if (!user.isThisUser(this->_data)) return;
        const Json::Value &position = data["data"];
        this->_object.getTransform().getPosition().setX(this->_object.getTransform().getPosition().getX() + position.get("x", 0).asFloat() * 1000 * (static_cast<float>(this->_clock.getMicroSeconds()) / 1000000));
        this->_object.getTransform().getPosition().setY(this->_object.getTransform().getPosition().getY() + position.get("y", 0).asFloat() * 1000 * (static_cast<float>(this->_clock.getMicroSeconds()) / 1000000));
        this->_clock.restart();
    });
    UnitiNetEngine::Uniti::getInstance().getEventManager().addEventListener("vesselShoot", [&] (UnitiNetEngine::IUser &user, const Json::Value &data) {
        if (!user.isThisUser(this->_data)) return;
        this->spawnMissile(300, 10);
    });
}

void VesselAlly::update() {
    Json::Value value;
    Json::Value position;
    value["id"] = this->_data;
    position["x"] = this->_object.getTransform().getPosition().getX();
    position["y"] = this->_object.getTransform().getPosition().getY();
    value["position"] = position;
    value["life"] = this->_life;
    for (auto &user : UnitiNetEngine::Uniti::getInstance().getUserManager().getUsers()) {
        Json::Value data;
        if (user.get()->getSendEvent().getEvents().contains("Vessel"))
            data = user.get()->getSendEvent().getEvents().at("Vessel");
        data[this->_object.getName()] = value;
        user.get()->getSendEvent().addEvent("Vessel", data);
    }
    this->checkCollisionWithMissile();
}

void VesselAlly::awake(const Json::Value &value) {
    this->_data = value;
}

VesselAlly::VesselAlly(UnitiNetEngine::Object &object, Entity::Type type, float life, float speed, Entity::Box box)
: Entity(object, type, life, speed, box) {}

void VesselAlly::createVesselAlly(const UnitiNetEngine::IUser &user) {
    auto object = std::make_unique<UnitiNetEngine::Object>(user.getUserInfo().asString(), UnitiNetEngine::Uniti::getInstance().getObjectManager().getSendEvent());
    object->getScriptManager().addScript("VesselAlly", std::make_unique<VesselAlly>(*object, ALLY, 100, 200, Box(0, 0, 150, 150)));
    object->getScriptManager().getScript("VesselAlly").awake(user.getUserInfo());
    object->getScriptManager().start();
    UnitiNetEngine::Uniti::getInstance().getObjectManager().addObject(std::move(object));
}
