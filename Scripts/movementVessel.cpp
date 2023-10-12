//
// Created by youba on 09/10/2023.
//

#include <iostream>
#include "movementVessel.hpp"
#include "Uniti.hpp"

void movementVessel::start() {
    std::cout << "je commence" << std::endl;
    UnitiNetEngine::Uniti::getInstance().getEventManager().addEventListener("vesselMovement", [&] (UnitiNetEngine::IUser &user, const Json::Value &data) {
        if (!user.isThisUser(this->_data)) return;
        const Json::Value &position = data["data"];
        std::cout << position << std::endl;
        this->_object.getTransform().getPosition().setX(position.get("x", this->_object.getTransform().getPosition().getX()).asFloat());
        this->_object.getTransform().getPosition().setY(position.get("y", this->_object.getTransform().getPosition().getY()).asFloat());
    });
}

void movementVessel::update() {
    Json::Value value;
    Json::Value position;
    value["id"] = this->_data;
    position["x"] = this->_object.getTransform().getPosition().getX();
    position["y"] = this->_object.getTransform().getPosition().getY();
    value["position"] = position;
    this->_object.getsendEvent().addEvent("VesselPosition", value);
}

void movementVessel::awake(const Json::Value &value) {
    this->_data = value;
}
