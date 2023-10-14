//
// Created by youba on 14/10/2023.
//

#include "Sniper.hpp"
#include "Uniti.hpp"

int Sniper::_count = 0;

void Sniper::CreateSniper() {
    Sniper::_count = (Sniper::_count >= 10000) ? 0 : Sniper::_count + 1;
    auto object = std::make_unique<UnitiNetEngine::Object>("Sniper" + std::to_string(Sniper::_count), UnitiNetEngine::Uniti::getInstance().getObjectManager().getSendEvent());
    object->getScriptManager().addScript("Sniper", std::make_unique<Sniper>(*object, ENEMY, 100, 100, Box(0, 0, 32, 32)));
    object->getScriptManager().getScript("Sniper").awake({});
    object->getScriptManager().start();
    object->getTransform().getPosition().setX(2000);
    object->getTransform().getPosition().setY(std::rand() % 950);
    UnitiNetEngine::Uniti::getInstance().getObjectManager().addObject(std::move(object));
}

Sniper::Sniper(UnitiNetEngine::Object &object, Entity::Type type, float life, float speed, Entity::Box box)
: Entity(object, type, life, speed, box, 30) {}

void Sniper::start() {}

void Sniper::update() {
    this->_object.getTransform().getPosition().setX(this->_object.getTransform().getPosition().getX() - this->_speed * (static_cast<float>(this->_clock.getMicroSeconds()) / 1000000));
    if (this->_object.getTransform().getPosition().getX() < -100) {
        this->destroyEntity();
        return;
    }
    this->_clock.restart();
    if (this->_missile.getSeconds() >= 5) {
        this->_missile.restart();
        auto allies = this->getAlliesVessel();
        if (!allies.empty()) {
            this->spawnMissile(400, this->_damage, allies[std::rand() % allies.size()], {0, 0, 32, 32});
        }
    }
    this->sendPosition({});
    this->checkCollisionWithMissile();
}

void Sniper::awake(const Json::Value &value) {}

void Sniper::onOverlap(Entity &entity) {
    Entity::onOverlap(entity);
    if (entity.getType() != ALLY) return;
    entity.setLife(entity.getLife() - 30);
    this->destroyEntity();
}
