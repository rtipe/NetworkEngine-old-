//
// Created by youba on 01/10/2023.
//

#pragma once

#include <mutex>
#include "User/IUser.hpp"

namespace UnitiNetEngine {
    class Position {
        public:
            float getX();
            float getY();
            float getZ();
            void setX(float value);
            void setY(float value);
            void setZ(float value);
        private:
            float _x;
            float _y;
            float _z;
            std::mutex _mutex;
    };
}
