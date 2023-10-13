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
    Entity(UnitiNetEngine::Object &object, Type type, float life, float speed, Box box):
    _object(object),
    _type(type),
    _life(life),
    _speed(speed),
    _box(box) {}
    void checkCollisionWithMissile();
    void spawnMissile(float speed, float damage);
    void spawnMissile(float speed, float damage, std::tuple<float, float> direction, Box box);
    void spawnMissile(float speed, float damage, UnitiNetEngine::Object &to, Box box);
    void destroyEntity();
    void sendPosition();
    UnitiNetEngine::Clock &getClock();
private:
    UnitiNetEngine::Clock _clock;
    float _speed;
    Type _type;
    Box _box;
protected:
    UnitiNetEngine::Object &_object;
    float _life;
};
