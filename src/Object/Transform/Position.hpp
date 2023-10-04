//
// Created by youba on 01/10/2023.
//

#pragma once

#include <mutex>
#include "User/IUser.hpp"

namespace UnitiNetEngine {
    class Object;
    class Position {
        public:
            Position(Object &object);
            float getX();
            float getY();
            float getZ();
            void setX(float value);
            void setY(float value);
            void setZ(float value);
        private:
            float _x = 0;
            float _y = 0;
            float _z = 0;
            Object &_object;
            std::mutex _mutex;
    };
}
