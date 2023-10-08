//
// Created by youba on 01/10/2023.
//

#include <string>
#include <fstream>
#include <filesystem>
#include "ProjectInfo.hpp"

namespace UnitiNetEngine {

    ProjectInfo::ProjectInfo(const std::string &projectPath) {
        std::ifstream file(projectPath);
        Json::Value project;
        file >> project;

        this->name = project.get("name", "undefined").asString();
        this->portUDP = project.get("portUDP", 0).asInt();
        this->portTCP = project.get("portTCP", 0).asInt();
        this->latence = project.get("latence", 15).asInt();
        this->publicScenePath = project.get("publicScenePath", "").asString();
        this->privateScenePath = project.get("privateScenePath", "").asString();

        std::ifstream filePublicScene(this->publicScenePath);
        filePublicScene >> this->privateScene;
        std::ifstream filePrivateScene(this->privateScenePath);
        filePrivateScene >> this->publicScene;
    }
}
