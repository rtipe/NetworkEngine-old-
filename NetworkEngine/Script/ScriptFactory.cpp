//
// Created by youba on 01/10/2023.
//

#include "ScriptFactory.hpp"

namespace UnitiNetEngine {
    std::unique_ptr<IScript> ScriptFactory::createScript(const std::string &name, Object &object) {
        return this->creators[name](object);
    }
}