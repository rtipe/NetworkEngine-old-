//
// Created by youba on 01/10/2023.
//

#pragma once

namespace UnitiNetEngine {
    class Scale {
        public:
            float getX() const;
            float getY() const;
            void setX(float value);
            void setY(float value);
            void setX(IUser &user, float value);
            void setY(IUser &user, float value);
        private:
            float _x;
            float _y;
            std::mutex _mutex;
    };
}

