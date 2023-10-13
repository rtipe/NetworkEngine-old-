//
// Created by youba on 13/10/2023.
//

#pragma once

#include "Entity.hpp"

class VesselAlly : public Entity {
public:
    static void createVesselAlly(const UnitiNetEngine::IUser &user);
    VesselAlly(UnitiNetEngine::Object &object, Type type, float life, float speed, Box box);
    void start() override;
    void update() override;
    void awake(const Json::Value &value) override;
private:
    Json::Value _data;
    UnitiNetEngine::Clock _clock;
};
