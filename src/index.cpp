//
// Created by root on 10/4/23.
//

#include <iostream>
#include "Uniti.hpp"
#include "User.hpp"
#include "Enemies/EnemiesHandler.hpp"
#include "UserController.hpp"

int main() {
    try {
        std::srand(time(NULL));
        UnitiNetEngine::Uniti::init("../json/project.json");

        UnitiNetEngine::Uniti::getInstance().getUserManager().addUserCreator<User>();

        //UnitiNetEngine::Uniti::getInstance().getScriptFactory().addScript<VesselAlly>("VesselAlly");
        //UnitiNetEngine::Uniti::getInstance().getScriptFactory().addScript<Missile>("Missile");

        UnitiNetEngine::Uniti::getInstance().getScriptFactory().addScript<EnemiesHandler>("EnemiesHandler");
        UnitiNetEngine::Uniti::getInstance().getScriptFactory().addScript<UserController>("UserController");

        UnitiNetEngine::Uniti::getInstance().start();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}