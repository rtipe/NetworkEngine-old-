//
// Created by youba on 01/10/2023.
//

#pragma once

#include <memory>
#include <string>
#include <map>
#include "IScript.hpp"

namespace UnitiNetEngine {
    class ScriptManager {
        public:
            void update();
            void start();
            void addScript(const std::string &name, std::unique_ptr<IScript> script);
            void deleteScript(const std::string &name);
            IScript &getScript(const std::string &name);
            std::map<std::string, std::unique_ptr<IScript>> &getScripts();
        private:
            std::map<std::string, std::unique_ptr<IScript>> _scripts;
    };
}
