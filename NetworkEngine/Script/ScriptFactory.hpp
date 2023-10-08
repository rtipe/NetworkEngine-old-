//
// Created by youba on 01/10/2023.
//

#pragma once

#include <memory>
#include <functional>
#include "IScript.hpp"
#include "../Object/Object.hpp"

namespace UnitiNetEngine {
    using creatorFunction = std::function<std::unique_ptr<IScript>(Object & object)>;
    class ScriptFactory {
        public:
            std::unique_ptr<IScript> createScript(const std::string &name, Object &object);
            template<typename OBJECT>
            void addScript(const std::string &name) {
                this->creators[name] = [&](Object &object) -> std::unique_ptr<IScript> {
                    return std::make_unique<OBJECT>(object);
                };
            }
        private:
            std::map<std::string, creatorFunction> creators;
    };
}
