//
// Created by youba on 14/10/2023.
//

#pragma once

#include "Entity.hpp"

class Tank : public Entity {
public:
    static void CreateTank();
    Tank(UnitiNetEngine::Object &object, Type type, float life, float speed, Box box);
    void start() override;
    void update() override;
    void awake(const Json::Value &value) override;
    void onOverlap(Entity &entity) override;
private:
    static int _count;
    UnitiNetEngine::Clock _clock;
    UnitiNetEngine::Clock _missile;
};
