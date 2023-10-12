//
// Created by youba on 12/10/2023.
//

#pragma once

#include "IScript.hpp"
#include "Object.hpp"
#include "Entity.hpp"

class Missile : public UnitiNetEngine::IScript {
public:
    static void createMissile(const std::string &name, Entity::Box box, float speed, float damage, std::tuple<float, float> direction, Entity::Type type);
    Missile(UnitiNetEngine::Object &object, Entity::Box box, float speed, float damage, std::tuple<float, float> direction, Entity::Type type):
    _object(object),
    _box(box),
    _speed(speed),
    _damage(damage),
    _direction(direction),
    _type(type) {}
    void start() override;
    void update() override;
    void awake(const Json::Value &value) override;
    bool isCollided(const Entity::Box &box) const;
    void destroyMissile();
    float getDamage() const;
    Entity::Type getType() const;
private:
    UnitiNetEngine::Object &_object;
    UnitiNetEngine::Clock _clock;
    float _speed;
    std::tuple<float, float> _direction;
    float _damage;
    Entity::Box _box;
    Entity::Type _type;
};
