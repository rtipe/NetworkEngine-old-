//
// Created by youba on 13/10/2023.
//

#include "VesselWeapon.hpp"
#include "Uniti.hpp"

int VesselWeapon::_count = 0;

void VesselWeapon::CreateVesselWeapon() {
    VesselWeapon::_count = (VesselWeapon::_count >= 10000) ? 0 : VesselWeapon::_count + 1;
    auto object = std::make_unique<UnitiNetEngine::Object>("VesselWeapon" + std::to_string(VesselWeapon::_count), UnitiNetEngine::Uniti::getInstance().getObjectManager().getSendEvent());
    object->getScriptManager().addScript("VesselWeapon", std::make_unique<VesselWeapon>(*object, ALLY, 100, 250, Box(0, 0, 50, 50)));
    object->getScriptManager().getScript("VesselWeapon").awake({});
    object->getScriptManager().start();
    object->getTransform().getPosition().setX(2000);
    object->getTransform().getPosition().setY(std::rand() % 950);
    UnitiNetEngine::Uniti::getInstance().getObjectManager().addObject(std::move(object));
}

VesselWeapon::VesselWeapon(UnitiNetEngine::Object &object, Entity::Type type, float life, float speed, Entity::Box box):
Entity(object, type, life, speed, box) {}

void VesselWeapon::start() {}

void VesselWeapon::update() {
    this->_object.getTransform().getPosition().setX(this->_object.getTransform().getPosition().getX() - this->_speed * (static_cast<float>(this->_clock.getMicroSeconds()) / 1000000));
    if (this->_object.getTransform().getPosition().getX() < -100) {
        this->destroyEntity();
        return;
    }
    this->_clock.restart();
    this->sendPosition({});
}

void VesselWeapon::awake(const Json::Value &value) {}

void VesselWeapon::onOverlap(Entity &entity) {
    if (entity.getType() != ALLY) return;
    Entity::onOverlap(entity);
    entity.setDamage(entity.getDamage() + 5);
    this->destroyEntity();
}
