//
// Created by youba on 13/10/2023.
//

#pragma once

#include "IScript.hpp"
#include "Object.hpp"
#include "Clock.hpp"

class UserController : public UnitiNetEngine::IScript {
public:
    UserController(UnitiNetEngine::Object &object);
    void start() override;
    void update() override;
    void awake(const Json::Value &value) override;
private:
    UnitiNetEngine::Object &_object;
    UnitiNetEngine::Clock _clock;
};
