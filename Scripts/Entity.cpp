//
// Created by youba on 12/10/2023.
//

#include "Entity.hpp"
#include "Uniti.hpp"
#include "Missile.hpp"

void Entity::checkCollisionWithMissile() {
    Box collision(
        this->_object.getTransform().getPosition().getX(),
        this->_object.getTransform().getPosition().getY(),
        this->_box.width,
        this->_box.height
    );
    for (auto &object : UnitiNetEngine::Uniti::getInstance().getObjectManager().getObjects()) {
        if (!object.second->getScriptManager().getScripts().contains("Missile")) return;
        Missile &missile = dynamic_cast<Missile &>(object.second->getScriptManager().getScript("Missile"));
        if (missile.isCollided(collision) && missile.getType() != this->_type) {
            this->_life -= missile.getDamage();
            missile.destroyMissile();
            if (this->_life <= 0) {
                this->destroyEntity();
                break;
            }
        }
    }
}

void Entity::spawnMissile(float speed, float damage) {
    Missile::createMissile("basicMissile", {
        static_cast<int>(this->_object.getTransform().getPosition().getX()),
        static_cast<int>(this->_object.getTransform().getPosition().getY()),
        100,
        20
    }, speed, damage,
    (this->_type == ENEMY) ? std::tuple<float, float>(-1, 0) : std::tuple<float, float>(1, 0),
    this->_type);
}


void Entity::destroyEntity() {
    UnitiNetEngine::Uniti::getInstance().getObjectManager().removeObject(this->_object.getName());
    for (auto &user : UnitiNetEngine::Uniti::getInstance().getUserManager().getUsers())
        user.get()->getSendEvent().addEvent("destroyEntity", this->_object.getName());
}

void Entity::spawnMissile(float speed, float damage, std::tuple<float, float> direction, Box box) {
    Missile::createMissile("basicMissile", {
        static_cast<int>(this->_object.getTransform().getPosition().getX()),
        static_cast<int>(this->_object.getTransform().getPosition().getY()),
        box.width,
        box.height
    }, speed, damage,
    direction,
    this->_type);
}

void Entity::spawnMissile(float speed, float damage, UnitiNetEngine::Object &to, Box box) {
    float x = to.getTransform().getPosition().getX() - this->_object.getTransform().getPosition().getX();
    float y = to.getTransform().getPosition().getY() - this->_object.getTransform().getPosition().getY();
    auto length = std::sqrt(x * x + y * y);
    Missile::createMissile("basicMissile", {
        static_cast<int>(this->_object.getTransform().getPosition().getX()),
        static_cast<int>(this->_object.getTransform().getPosition().getY()),
        box.width,
        box.height
    }, speed, damage,
    (length == 0) ? std::tuple<float, float>(1, 1) : std::tuple<float, float>(x / length, y / length),
    this->_type);
}

UnitiNetEngine::Clock &Entity::getClock() {
    return this->_clock;
}

void Entity::sendPosition() {
    Json::Value value;
    Json::Value position;
    value["id"] = this->_object.getName();
    position["x"] = this->_object.getTransform().getPosition().getX();
    position["y"] = this->_object.getTransform().getPosition().getY();
    value["position"] = position;
    this->_object.getsendEvent().addEvent("EntityPosition", value);
}
