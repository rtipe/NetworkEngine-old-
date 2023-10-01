//
// Created by youba on 01/10/2023.
//

#pragma once

namespace UnitiNetEngine {
    class IScript {
        public:
            virtual void start() = 0;
            virtual void update() = 0;
    };
}
