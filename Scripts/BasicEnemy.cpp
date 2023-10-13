//
// Created by youba on 13/10/2023.
//

#include <iostream>
#include "BasicEnemy.hpp"
#include "Uniti.hpp"

int BasicEnemy::_count = 0;

void BasicEnemy::CreateBasicEnemy() {
    BasicEnemy::_count = (BasicEnemy::_count >= 10000) ? 0 : BasicEnemy::_count + 1;
    auto object = std::make_unique<UnitiNetEngine::Object>("BasicEnemy" + std::to_string(BasicEnemy::_count), UnitiNetEngine::Uniti::getInstance().getObjectManager().getSendEvent());
    object->getScriptManager().addScript("BasicEnemy", std::make_unique<BasicEnemy>(*object, ENEMY, 100, 150, Box(0, 0, 150, 150)));
    object->getScriptManager().getScript("BasicEnemy").awake({});
    object->getScriptManager().start();
    object->getTransform().getPosition().setX(2000);
    object->getTransform().getPosition().setY(std::rand() % 950);
    UnitiNetEngine::Uniti::getInstance().getObjectManager().addObject(std::move(object));
}

BasicEnemy::BasicEnemy(UnitiNetEngine::Object &object, Entity::Type type, float life, float speed, Entity::Box box)
: Entity(object, type, life, speed, box) {}

void BasicEnemy::start() { }

void BasicEnemy::update() {
    this->_object.getTransform().getPosition().setX(this->_object.getTransform().getPosition().getX() - this->_speed * (static_cast<float>(this->_clock.getMicroSeconds()) / 1000000));
    if (this->_object.getTransform().getPosition().getX() < -100) {
        this->destroyEntity();
        return;
    }
    this->_clock.restart();
    if (this->_missile.getSeconds() >= 2) {
        this->_missile.restart();
        this->spawnMissile(300, this->_damage);
    }
    this->sendPosition({});
    this->checkCollisionWithMissile();
}

void BasicEnemy::awake(const Json::Value &value) {}

void BasicEnemy::onOverlap(Entity &entity) {
    Entity::onOverlap(entity);
    entity.setLife(entity.getLife() - 30);
    this->destroyEntity();
}
