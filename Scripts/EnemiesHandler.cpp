//
// Created by youba on 13/10/2023.
//

#include <iostream>
#include "EnemiesHandler.hpp"
#include "BasicEnemy.hpp"
#include "VesselHeal.hpp"
#include "VesselWeapon.hpp"

EnemiesHandler::EnemiesHandler(UnitiNetEngine::Object &object): _object(object) {}

void EnemiesHandler::start() {
}

void EnemiesHandler::update() {
    if (this->_clock.getSeconds() >= 5) {
        BasicEnemy::CreateBasicEnemy();
        BasicEnemy::CreateBasicEnemy();
        this->_clock.restart();
    }
    if (this->_heal.getSeconds() >= 5) {
        VesselHeal::CreateVesselHeal();
        VesselWeapon::CreateVesselWeapon();
        this->_heal.restart();
    }
}

void EnemiesHandler::awake(const Json::Value &value) {

}
