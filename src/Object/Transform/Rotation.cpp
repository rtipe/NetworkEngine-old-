//
// Created by youba on 01/10/2023.
//

#include "Rotation.hpp"

namespace UnitiNetEngine {

    float Rotation::getValue() {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        return this->_value;
    }

    void Rotation::setValue(float value) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_value = value;
    }
}
