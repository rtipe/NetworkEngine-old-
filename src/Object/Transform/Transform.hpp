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
            const Position &getPosition() const;
            Position &getPosition();
            const Rotation &getRotation() const;
            Rotation &getRotation();
            const Scale &getScale() const;
            Scale &getScale();
        private:
            Position _position;
            Rotation _rotation;
            Scale _scale;
    };
}
