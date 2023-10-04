//
// Created by youba on 01/10/2023.
//

#pragma once

#include <mutex>
#include "Event/sendEventManager.hpp"

namespace UnitiNetEngine {
    class Object;
    class Rotation {
        public:
            Rotation(Object &object);
            float getValue();
            void setValue(float value);
        private:
            float _value = 0;
            Object &_object;
            std::mutex _mutex;
    };
}
