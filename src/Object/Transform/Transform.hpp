//
// Created by youba on 01/10/2023.
//

#pragma once

#include "Position.hpp"
#include "Rotation.hpp"
#include "Scale.hpp"

namespace UnitiNetEngine {
    class Transform {
        public:
            Position &getPosition();
            Rotation &getRotation();
            Scale &getScale();
        private:
            Position _position;
            Rotation _rotation;
            Scale _scale;
    };
}
