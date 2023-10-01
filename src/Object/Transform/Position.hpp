//
// Created by youba on 01/10/2023.
//

#pragma once

#include <mutex>
#include "User/IUser.hpp"

namespace UnitiNetEngine {
    class Position {
        public:
            float getX() const;
            float getY() const;
            float getZ() const;
            void setX(float value);
            void setY(float value);
            void setZ(float value);
            void setX(IUser &user, float value);
            void setY(IUser &user, float value);
            void setZ(IUser &user, float value);
        private:
            float _x;
            float _y;
            float _z;
            std::mutex _mutex;
    };
}
