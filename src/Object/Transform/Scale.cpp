//
// Created by youba on 01/10/2023.
//

#include "Scale.hpp"

namespace UnitiNetEngine {

    float Scale::getX() {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        return this->_x;
    }

    float Scale::getY() {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        return this->_y;
    }

    void Scale::setX(float value) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_x = value;
    }

    void Scale::setY(float value) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_y = value;
    }
}
