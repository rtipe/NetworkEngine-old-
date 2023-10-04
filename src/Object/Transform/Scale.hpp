//
// Created by youba on 01/10/2023.
//

#pragma once

#include <mutex>
#include "Event/sendEventManager.hpp"

namespace UnitiNetEngine {
    class Object;
    class Scale {
        public:
            Scale(Object &object);
            float getX();
            float getY();
            void setX(float value);
            void setY(float value);
        private:
            Object &_object;
            float _x = 0;
            float _y = 0;
            std::mutex _mutex;
    };
}

