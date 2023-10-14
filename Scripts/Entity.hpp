//
// Created by youba on 12/10/2023.
//

#pragma once

#include "IScript.hpp"
#include "Object.hpp"
#include "Clock.hpp"

class Entity : public UnitiNetEngine::IScript {
public:
    struct Box {
        Box(int _x, int _y, int _width, int _height): x(_x), y(_y), width(_width), height(_height) {}
        int x;
        int y;
        int width;
        int height;
    };
    enum Type {
        ENEMY,
        ALLY
    };
    Entity(UnitiNetEngine::Object &object, Type type, float life, float speed, Box box, float damage = 10):
    _object(object),
    _type(type),
    _life(life),
    _speed(speed),
    _box(box),
    _damage(damage),
    _shootPosition(0, 0) {}
    void checkCollisionWithMissile();
    void spawnMissile(float speed, float damage);
    void spawnMissile(float speed, float damage, std::tuple<float, float> direction, Box box);
    void spawnMissile(float speed, float damage, UnitiNetEngine::Object &to, Box box);
    void destroyEntity();
    void sendPosition(const Json::Value &info);
    UnitiNetEngine::Clock &getClock();
    bool isCollided(const Entity::Box &box) const;
    virtual void onOverlap(Entity &entity);
    void setLife(float life);
    void setDamage(float damage);
    float getLife() const;
    float getDamage() const;
    Type getType() const;
    Box getBox() const;
    std::vector<std::reference_wrapper<UnitiNetEngine::Object>> getAlliesVessel();
private:
    UnitiNetEngine::Clock _clock;
    Type _type;
    Box _box;
protected:
    UnitiNetEngine::Object &_object;
    float _life;
    float _speed;
    float _damage;
    std::tuple<int, int> _shootPosition;
};
