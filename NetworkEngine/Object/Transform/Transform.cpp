//
// Created by youba on 01/10/2023.
//

#include "Transform.hpp"

namespace UnitiNetEngine {
    Position &Transform::getPosition() {
        return this->_position;
    }

    Rotation &Transform::getRotation() {
        return this->_rotation;
    }

    Scale &Transform::getScale() {
        return this->_scale;
    }

    Transform::Transform(Object &object):
    _object(object),
    _scale(object),
    _rotation(object),
    _position(object) {
    }
}