//
// Created by youba on 01/10/2023.
//

#include "Rotation.hpp"
#include "Object/Object.hpp"

namespace UnitiNetEngine {

    float Rotation::getValue() {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        return this->_value;
    }

    void Rotation::setValue(float value) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_value = value;
        Json::Value data;
        data["name"] = this->_object.getName();
        data["value"] = value;
        this->_object.getsendEvent().addEvent("ROTATION", data);
    }

    Rotation::Rotation(Object &object): _object(object) {

    }
}
