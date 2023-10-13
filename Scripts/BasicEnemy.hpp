//
// Created by youba on 13/10/2023.
//

#pragma once

#include "Entity.hpp"

class BasicEnemy : public Entity {
public:
    static void CreateBasicEnemy();
    BasicEnemy(UnitiNetEngine::Object &object, Type type, float life, float speed, Box box);
    void start() override;
    void update() override;
    void awake(const Json::Value &value) override;
private:
    static int _count;
    UnitiNetEngine::Clock _clock;
    UnitiNetEngine::Clock _missile;
};
