//
// Created by youba on 01/10/2023.
//

#include "Scale.hpp"
#include "Object/Object.hpp"

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
        Json::Value data;
        data["name"] = this->_object.getName();
        data["value"] = value;
        this->_object.getsendEvent().addEvent("SCALE_X", data);
    }

    void Scale::setY(float value) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_y = value;
        Json::Value data;
        data["name"] = this->_object.getName();
        data["value"] = value;
        this->_object.getsendEvent().addEvent("SCALE_Y", data);
    }

    Scale::Scale(Object &object): _object(object) {

    }
}
