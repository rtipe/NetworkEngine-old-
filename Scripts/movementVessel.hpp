//
// Created by youba on 09/10/2023.
//

#pragma once

#include "Object.hpp"
#include "IScript.hpp"
#include "Clock.hpp"

class movementVessel : public UnitiNetEngine::IScript {
public:
    movementVessel(UnitiNetEngine::Object &object): _object(object) {}
    void start() override;
    void update() override;
    void awake(const Json::Value &value) override;
private:
    UnitiNetEngine::Object &_object;
    Json::Value _data;
    UnitiNetEngine::Clock _clock;
};
