//
// Created by youba on 14/10/2023.
//

#include "Boss.hpp"
#include "Uniti.hpp"

int Boss::_count = 0;

void Boss::CreateBoss() {
    Boss::_count = (Boss::_count >= 10000) ? 0 : Boss::_count + 1;
    auto object = std::make_unique<UnitiNetEngine::Object>("Boss" + std::to_string(Boss::_count), UnitiNetEngine::Uniti::getInstance().getObjectManager().getSendEvent());
    object->getScriptManager().addScript("Boss", std::make_unique<Boss>(*object, ENEMY, 100, 50, Box(0, 0, 260, 143)));
    object->getScriptManager().getScript("Boss").awake({});
    object->getScriptManager().start();
    object->getTransform().getPosition().setX(2000);
    object->getTransform().getPosition().setY(1080 - 143);
    UnitiNetEngine::Uniti::getInstance().getObjectManager().addObject(std::move(object));
}

Boss::Boss(UnitiNetEngine::Object &object, Entity::Type type, float life, float speed, Entity::Box box)
: Entity(object, type, life, speed, box, 25) {}

void Boss::start() {}

void Boss::update() {
    this->_object.getTransform().getPosition().setX(this->_object.getTransform().getPosition().getX() - this->_speed * (static_cast<float>(this->_clock.getMicroSeconds()) / 1000000));
    if (this->_object.getTransform().getPosition().getX() < -100) {
        this->destroyEntity();
        return;
    }
    this->_clock.restart();
    if (this->_missile.getSeconds() >= 1) {
        this->_missile.restart();
        auto allies = this->getAlliesVessel();
        if (!allies.empty()) {
            this->spawnMissile(300, this->_damage, allies[std::rand() % allies.size()], {0, 0, 32, 32});
        }
    }
    this->sendPosition({});
    this->checkCollisionWithMissile();
}

void Boss::awake(const Json::Value &value) {}

void Boss::onOverlap(Entity &entity) {
    Entity::onOverlap(entity);
    if (entity.getType() != ALLY) return;
    entity.setLife(entity.getLife() - 130);
    this->destroyEntity();
}
