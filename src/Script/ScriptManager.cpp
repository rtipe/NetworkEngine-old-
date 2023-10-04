//
// Created by youba on 01/10/2023.
//

#include "ScriptManager.hpp"

namespace UnitiNetEngine {
    void ScriptManager::update() {
        for (auto &script : this->_scripts) {
            script.second->update();
        }
    }

    void ScriptManager::start() {
        for (auto &script : this->_scripts) {
            script.second->start();
        }
    }

    void ScriptManager::addScript(const std::string &name, std::unique_ptr<IScript> script) {
        this->_scripts[name] = std::move(script);
    }

    void ScriptManager::deleteScript(const std::string &name) {
        this->_scripts.erase(name);
    }

    IScript &ScriptManager::getScript(const std::string &name) {
        return *this->_scripts[name];
    }

    std::map<std::string, std::unique_ptr<IScript>> &ScriptManager::getScripts() {
        return this->_scripts;
    }
}