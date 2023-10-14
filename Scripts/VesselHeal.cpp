//
// Created by youba on 13/10/2023.
//

#include "VesselHeal.hpp"
#include "Uniti.hpp"

int VesselHeal::_count = 0;

void VesselHeal::CreateVesselHeal() {
    VesselHeal::_count = (VesselHeal::_count >= 10000) ? 0 : VesselHeal::_count + 1;
    auto object = std::make_unique<UnitiNetEngine::Object>("VesselHeal" + std::to_string(VesselHeal::_count), UnitiNetEngine::Uniti::getInstance().getObjectManager().getSendEvent());
    object->getScriptManager().addScript("VesselHeal", std::make_unique<VesselHeal>(*object, ALLY, 100, 200, Box(0, 0, 50, 50)));
    object->getScriptManager().getScript("VesselHeal").awake({});
    object->getScriptManager().start();
    object->getTransform().getPosition().setX(2000);
    object->getTransform().getPosition().setY(std::rand() % 950);
    UnitiNetEngine::Uniti::getInstance().getObjectManager().addObject(std::move(object));
}

void VesselHeal::start() {}

void VesselHeal::update() {
    this->_object.getTransform().getPosition().setX(this->_object.getTransform().getPosition().getX() - this->_speed * (static_cast<float>(this->_clock.getMicroSeconds()) / 1000000));
    if (this->_object.getTransform().getPosition().getX() < -100) {
        this->destroyEntity();
        return;
    }
    this->_clock.restart();
    this->sendPosition({});
}

void VesselHeal::awake(const Json::Value &value) {

}

void VesselHeal::onOverlap(Entity &entity) {
    if (entity.getType() != ALLY) return;
    Entity::onOverlap(entity);
    entity.setLife(entity.getLife() + 30);
    this->destroyEntity();
}

VesselHeal::VesselHeal(UnitiNetEngine::Object &object, Entity::Type type, float life, float speed, Entity::Box box):
Entity(object, type, life, speed, box) {}
