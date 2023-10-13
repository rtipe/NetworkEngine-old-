//
// Created by youba on 13/10/2023.
//

#pragma once


#include "Entity.hpp"

class VesselHeal : public Entity {
public:
    static void CreateVesselHeal();
    VesselHeal(UnitiNetEngine::Object &object, Entity::Type type, float life, float speed, Entity::Box box);
    void start() override;
    void update() override;
    void awake(const Json::Value &value) override;
    void onOverlap(Entity &entity) override;
private:
    static int _count;
    UnitiNetEngine::Clock _clock;
};
