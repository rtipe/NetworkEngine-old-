//
// Created by youba on 01/10/2023.
//

#include "Position.hpp"

namespace UnitiNetEngine {
    float Position::getX() {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        return this->_x;
    }

    float Position::getY() {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        return this->_y;
    }

    float Position::getZ() {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        return this->_z;
    }

    void Position::setX(float value) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_x = value;
    }

    void Position::setY(float value) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_y = value;
    }

    void Position::setZ(float value) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_z = value;
    }
}