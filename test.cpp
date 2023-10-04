//
// Created by root on 10/4/23.
//

#include <iostream>
#include "Uniti.hpp"

int main() {
    try {
        UnitiNetEngine::Uniti::getInstance();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}