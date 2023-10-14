//
// Created by youba on 14/10/2023.
//

#include "Tank.hpp"
#include "Uniti.hpp"

int Tank::_count = 0;

void Tank::CreateTank() {
    Tank::_count = (Tank::_count >= 10000) ? 0 : Tank::_count + 1;
    auto object = std::make_unique<UnitiNetEngine::Object>("Tank" + std::to_string(Tank::_count), UnitiNetEngine::Uniti::getInstance().getObjectManager().getSendEvent());
    object->getScriptManager().addScript("Tank", std::make_unique<Tank>(*object, ENEMY, 100, 75, Box(0, 0, 51, 59)));
    object->getScriptManager().getScript("Tank").awake({});
    object->getScriptManager().start();
    object->getTransform().getPosition().setX(2000);
    object->getTransform().getPosition().setY(std::rand() % 950);
    UnitiNetEngine::Uniti::getInstance().getObjectManager().addObject(std::move(object));
}

Tank::Tank(UnitiNetEngine::Object &object, Entity::Type type, float life, float speed, Entity::Box box)
: Entity(object, type, life, speed, box, 5) {}

void Tank::start() {}

void Tank::update() {
    this->_object.getTransform().getPosition().setX(this->_object.getTransform().getPosition().getX() - this->_speed * (static_cast<float>(this->_clock.getMicroSeconds()) / 1000000));
    if (this->_object.getTransform().getPosition().getX() < -100) {
        this->destroyEntity();
        return;
    }
    this->_clock.restart();
    if (this->_missile.getSeconds() >= 3) {
        this->_missile.restart();
        this->spawnMissile(350, this->_damage);
    }
    this->sendPosition({});
    this->checkCollisionWithMissile();
}

void Tank::awake(const Json::Value &value) {}

void Tank::onOverlap(Entity &entity) {
    Entity::onOverlap(entity);
    if (entity.getType() != ALLY) return;
    entity.setLife(entity.getLife() - 30);
    this->destroyEntity();
}
