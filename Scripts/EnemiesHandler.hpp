//
// Created by youba on 13/10/2023.
//

#pragma once


#include "Object.hpp"
#include "Clock.hpp"

class EnemiesHandler : public UnitiNetEngine::IScript {
public:
    EnemiesHandler(UnitiNetEngine::Object &object);
    void start() override;
    void update() override;
    void awake(const Json::Value &value) override;
private:
    UnitiNetEngine::Object &_object;
    UnitiNetEngine::Clock _clock;
};
