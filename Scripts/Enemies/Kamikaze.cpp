//
// Created by youba on 14/10/2023.
//

#include "Kamikaze.hpp"
#include "Uniti.hpp"

int Kamikaze::_count = 0;

void Kamikaze::CreateKamikaze() {
    Kamikaze::_count = (Kamikaze::_count >= 10000) ? 0 : Kamikaze::_count + 1;
    auto object = std::make_unique<UnitiNetEngine::Object>("Kamikaze" + std::to_string(Kamikaze::_count), UnitiNetEngine::Uniti::getInstance().getObjectManager().getSendEvent());
    object->getScriptManager().addScript("Kamikaze", std::make_unique<Kamikaze>(*object, ENEMY, 250, 100, Box(0, 0, 65, 130)));
    object->getScriptManager().getScript("Kamikaze").awake({});
    object->getScriptManager().start();
    object->getTransform().getPosition().setX(2000);
    object->getTransform().getPosition().setY(std::rand() % 950);
    UnitiNetEngine::Uniti::getInstance().getObjectManager().addObject(std::move(object));
}

Kamikaze::Kamikaze(UnitiNetEngine::Object &object, Entity::Type type, float life, float speed, Entity::Box box)
: Entity(object, type, life, speed, box) {}

void Kamikaze::start() {}

void Kamikaze::update() {
    this->_object.getTransform().getPosition().setX(this->_object.getTransform().getPosition().getX() - this->_speed * (static_cast<float>(this->_clock.getMicroSeconds()) / 1000000));
    if (this->_object.getTransform().getPosition().getX() < -100) {
        this->destroyEntity();
        return;
    }
    this->_clock.restart();
    this->sendPosition({});
    this->checkCollisionWithMissile();
}

void Kamikaze::awake(const Json::Value &value) {}

void Kamikaze::onOverlap(Entity &entity) {
    Entity::onOverlap(entity);
    if (entity.getType() != ALLY) return;
    entity.setLife(entity.getLife() - 90);
    this->destroyEntity();
}
