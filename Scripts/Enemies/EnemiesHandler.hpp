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
    Json::Value _data;
    UnitiNetEngine::Object &_object;
    UnitiNetEngine::Clock _clock;
    UnitiNetEngine::Clock _spawn;
    bool _isPaused = false;
};
