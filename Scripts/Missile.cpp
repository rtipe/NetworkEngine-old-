//
// Created by youba on 12/10/2023.
//

#include <iostream>
#include "Missile.hpp"
#include "Uniti.hpp"

void Missile::start() {}

void Missile::update() {
    this->_object.getTransform().getPosition().setX(this->_object.getTransform().getPosition().getX() + (std::get<0>(this->_direction) * this->_speed * (static_cast<float>(this->_clock.getMicroSeconds()) / 1000000)));
    this->_object.getTransform().getPosition().setY(this->_object.getTransform().getPosition().getY() + (std::get<1>(this->_direction) * this->_speed * (static_cast<float>(this->_clock.getMicroSeconds()) / 1000000)));
    this->_clock.restart();
    if (this->_object.getTransform().getPosition().getX() < -100 || this->_object.getTransform().getPosition().getX() > 1920 ||
        this->_object.getTransform().getPosition().getY() < -100 || this->_object.getTransform().getPosition().getY() > 1080) {
        this->destroyMissile();
        return;
    }
    Json::Value value;
    value["name"] = this->_object.getName();
    value["position"]["x"] = this->_object.getTransform().getPosition().getX();
    value["position"]["y"] = this->_object.getTransform().getPosition().getY();
    for (auto &user : UnitiNetEngine::Uniti::getInstance().getUserManager().getUsers())
        user.get()->getSendEvent().addEvent(this->_object.getName(), value);
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

int Missile::_count = 0;

void Missile::createMissile(const std::string &name, Entity::Box box, float speed, float damage, std::tuple<float, float> direction, Entity::Type type) {
    Missile::_count = (Missile::_count >= 10000) ? 0 : Missile::_count + 1;
    auto object = std::make_unique<UnitiNetEngine::Object>(name + std::to_string(Missile::_count), UnitiNetEngine::Uniti::getInstance().getObjectManager().getSendEvent());
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
    value["name"] = name + std::to_string(Missile::_count);
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
