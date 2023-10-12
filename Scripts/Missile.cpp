//
// Created by youba on 12/10/2023.
//

#include "Missile.hpp"
#include "Uniti.hpp"

void Missile::start() {}

void Missile::update() {
    float mult = this->_speed * (static_cast<float>(this->_clock.getMilliSeconds()) / 1000);
    this->_object.getTransform().getPosition().setX(this->_object.getTransform().getPosition().getX() * mult);
    this->_object.getTransform().getPosition().setY(this->_object.getTransform().getPosition().getY() * mult);
}

void Missile::awake(const Json::Value &value) { }

bool Missile::isCollided(const Entity::Box &box) const {
    float thisLeft = this->_object.getTransform().getPosition().getX();
    float thisRight = this->_object.getTransform().getPosition().getX() + this->_box.width;
    float thisTop = this->_object.getTransform().getPosition().getY();
    float thisBottom = this->_object.getTransform().getPosition().getY() + this->_box.height;

    float otherLeft = box.x;
    float otherRight = box.x + box.width;
    float otherTop = box.y;
    float otherBottom = box.y + box.height;

    return !(thisRight < otherLeft || thisLeft > otherRight || thisBottom < otherTop || thisTop > otherBottom);
}

void Missile::createMissile(const std::string &name, Entity::Box box, float speed, float damage, std::tuple<float, float> direction, Entity::Type type) {
    auto object = std::make_unique<UnitiNetEngine::Object>(name, UnitiNetEngine::Uniti::getInstance().getObjectManager().getSendEvent());
    object->getScriptManager().addScript("Missile", std::make_unique<Missile>(*object, box, speed, damage, direction, type));
    object->getScriptManager().start();
    object->getTransform().getPosition().setX(box.x);
    object->getTransform().getPosition().setY(box.y);
    UnitiNetEngine::Uniti::getInstance().getObjectManager().addObject(std::move(object));
    Json::Value value;
    value["position"]["x"] = box.x;
    value["position"]["y"] = box.y;
    value["speed"] = speed;
    value["direction"]["x"] = std::get<0>(direction);
    value["direction"]["y"] = std::get<1>(direction);
    value["name"] = name;
    for (auto &user : UnitiNetEngine::Uniti::getInstance().getUserManager().getUsers())
        user.get()->getSendEvent().addEvent("createMissile", value);
}

void Missile::destroyMissile() {
    UnitiNetEngine::Uniti::getInstance().getObjectManager().removeObject(this->_object.getName());
    for (auto &user : UnitiNetEngine::Uniti::getInstance().getUserManager().getUsers())
        user.get()->getSendEvent().addEvent("destroyMissile", this->_object.getName());
}

float Missile::getDamage() const {
    return this->_damage;
}

Entity::Type Missile::getType() const {
    return this->_type;
}
