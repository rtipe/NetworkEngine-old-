//
// Created by youba on 01/10/2023.
//

#pragma once

#include <json/value.h>

namespace UnitiNetEngine {
    class IScript {
        public:
            virtual void start() = 0;
            virtual void update() = 0;
            virtual void awake(const Json::Value &value) = 0;
    };
}
