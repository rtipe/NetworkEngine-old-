//
// Created by youba on 01/10/2023.
//

#pragma once

#include <mutex>
#include "Event/sendEventManager.hpp"
#include "Object/Object.hpp"

namespace UnitiNetEngine {
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
