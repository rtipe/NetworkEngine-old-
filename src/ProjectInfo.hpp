//
// Created by youba on 01/10/2023.
//

#pragma once

#include <json/value.h>
#include <string>

namespace UnitiNetEngine {
    struct ProjectInfo {
        public:
            explicit ProjectInfo(const std::string &projectPath);
            std::string name;
            std::string ip;
            std::string scenePath;
            int portUDP;
            int portTCP;
    };
}
