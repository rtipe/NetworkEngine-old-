//
// Created by youba on 13/10/2023.
//

#include <iostream>
#include "EnemiesHandler.hpp"
#include "BasicEnemy.hpp"
#include "Boss.hpp"
#include "Kamikaze.hpp"
#include "Sniper.hpp"
#include "Tank.hpp"
#include "VesselHeal.hpp"
#include "VesselWeapon.hpp"

EnemiesHandler::EnemiesHandler(UnitiNetEngine::Object &object): _object(object) {}

void EnemiesHandler::start() {}

void EnemiesHandler::update() {
    std::map<std::string, std::function<void()>> creators = {
        {"Boss", std::bind(Boss::CreateBoss)},
        {"Kamikaze", std::bind(Kamikaze::CreateKamikaze)},
        {"Sniper", std::bind(Sniper::CreateSniper)},
        {"Tank", std::bind(Tank::CreateTank)},
        {"BasicEnemy", std::bind(BasicEnemy::CreateBasicEnemy)}
    };
    if (this->_isPaused) {
        if (this->_clock.getSeconds() >= this->_data.get("pauseTime", 15).asInt()) {
            this->_isPaused = false;
            this->_clock.restart();
            return;
        }
        if (this->_spawn.getSeconds() >= this->_data.get("spawnPauseTime", 2).asInt()) {
            if (std::rand() % 100 <= this->_data.get("spawnVesselHeal", 20).asInt())
                VesselHeal::CreateVesselHeal();
            if (std::rand() % 100 <= this->_data.get("spawnVesselWeapon", 5).asInt())
                VesselWeapon::CreateVesselWeapon();
            this->_spawn.restart();
        }
    } else {
        if (this->_clock.getSeconds() >= this->_data.get("waveTime", 120).asInt()) {
            this->_isPaused = true;
            this->_clock.restart();
            return;
        }
        if (this->_spawn.getSeconds() >= this->_data.get("spawnTime", 2).asInt()) {
            for (auto &creator : creators) {
                if (std::rand() % 100 > this->_data.get(creator.first, 5).asInt()) continue;
                creator.second();
            }
            if (std::rand() % 100 <= this->_data.get("spawnVesselHeal", 20).asInt() / 2)
                VesselHeal::CreateVesselHeal();
            if (std::rand() % 100 <= this->_data.get("spawnVesselWeapon", 5).asInt() / 2)
                VesselWeapon::CreateVesselWeapon();
            this->_spawn.restart();
        }
    }
}

void EnemiesHandler::awake(const Json::Value &value) {
    this->_data = value;
}
