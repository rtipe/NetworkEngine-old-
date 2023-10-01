//
// Created by youba on 01/10/2023.
//

#pragma once

#include <json/value.h>
#include "Object/Transform/Transform.hpp"

namespace UnitiNetEngine {
    class Object {
        public:
            Object(const Json::Value &value);
            void setEnable(bool value);
            bool isEnable() const;
            const Transform &getTransform() const;
            Transform &getTransform();
        private:
            Transform _transform;
    };
}
