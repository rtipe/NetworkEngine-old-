//
// Created by root on 10/4/23.
//

#include <iostream>
#include "Uniti.hpp"
#include "User.hpp"
#include "movementVessel.hpp"

int main() {
    try {
        UnitiNetEngine::Uniti::init("../json/project.json");

        UnitiNetEngine::Uniti::getInstance().getUserManager().addUserCreator<User>();

        UnitiNetEngine::Uniti::getInstance().getScriptFactory().addScript<movementVessel>("movementVessel");

        UnitiNetEngine::Uniti::getInstance().start();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}