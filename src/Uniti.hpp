//
// Created by youba on 01/10/2023.
//

#pragma once

#include <string>
#include "ProjectInfo.hpp"
#include "Event/EventManager.hpp"
#include "Script/ScriptFactory.hpp"

namespace UnitiNetEngine {
    class Uniti {
        public:
            void init(const std::string &projectPath);
            void start();
            static Uniti &getInstance();
            const ProjectInfo &getProjectInfo() const;
            const EventManager &getEventManager() const;
            EventManager &getEventManager();
            ScriptFactory &getScriptFactory();
        private:
            Uniti(const std::string &projectPath);
            ProjectInfo _projectInfo;
            EventManager _eventManager;
            ScriptFactory _scriptFactory;
    };
}
