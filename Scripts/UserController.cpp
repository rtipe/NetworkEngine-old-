//
// Created by youba on 13/10/2023.
//

#include <iostream>
#include "UserController.hpp"
#include "Uniti.hpp"
#include "VesselAlly.hpp"

UserController::UserController(UnitiNetEngine::Object &object): _object(object) {}

void UserController::start() {
    UnitiNetEngine::Uniti::getInstance().getEventManager().addEventListener("vesselMovement", [&] (UnitiNetEngine::IUser &user, const Json::Value &data) {
        for (auto &object : UnitiNetEngine::Uniti::getInstance().getObjectManager().getObjects()) {
            if (!user.isThisUser(object.first)) continue;
            const Json::Value &position = data["data"];
            object.second->getTransform().getPosition().setX(object.second->getTransform().getPosition().getX() + position.get("x", 0).asFloat() * 1000 * (static_cast<float>(this->_clock.getMicroSeconds()) / 1000000));
            object.second->getTransform().getPosition().setY(object.second->getTransform().getPosition().getY() + position.get("y", 0).asFloat() * 1000 * (static_cast<float>(this->_clock.getMicroSeconds()) / 1000000));
            this->_clock.restart();
        }
    });
    UnitiNetEngine::Uniti::getInstance().getEventManager().addEventListener("vesselShoot", [&] (UnitiNetEngine::IUser &user, const Json::Value &data) {
        for (auto &object : UnitiNetEngine::Uniti::getInstance().getObjectManager().getObjects()) {
            if (!user.isThisUser(object.first)) continue;
            VesselAlly &entity = dynamic_cast<VesselAlly &>(object.second->getScriptManager().getScript("VesselAlly"));
            entity.spawnMissile(300, 10);
        }
    });
}

void UserController::update() {}

void UserController::awake(const Json::Value &value) {}
