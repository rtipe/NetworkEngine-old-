//
// Created by youba on 01/10/2023.
//

#pragma once

#include <mutex>

namespace UnitiNetEngine {
    class Rotation {
        public:
            float getValue();
            void setValue(float value);
        private:
            float _value;
            std::mutex _mutex;
    };
}
