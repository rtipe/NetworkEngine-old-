//
// Created by youba on 01/10/2023.
//

#pragma once

#include <mutex>

namespace UnitiNetEngine {
    class Scale {
        public:
            float getX();
            float getY();
            void setX(float value);
            void setY(float value);
        private:
            float _x;
            float _y;
            std::mutex _mutex;
    };
}

