//
// Created by youba on 01/10/2023.
//

#pragma once

namespace UnitiNetEngine {
    class Rotation {
        public:
            float getValue() const;
            void setValue(float value);
            void setValue(IUser &user, float value);
        private:
            float _value;
            std::mutex _mutex;
    };
}
