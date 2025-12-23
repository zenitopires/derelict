#include <derelict/graphics/shader_manager.hpp>
#include <derelict/logging/logger.hpp>

#include "glad/glad.h"

namespace derelict {
    void ShaderManager::AddShader(std::unique_ptr<Shader> shader, const std::string &name) {
        if (shaders.contains(name)) {
            logError("A shader with the name '{}' name already exists!", name);
            return;
        }
        shaders.emplace(name, std::move(shader));
    }

    void ShaderManager::AddShader(const std::string &vertexShader, const std::string &fragmentShader, const std::string& name) {
        if (shaders.contains(name)) {
            logWarn("A shader with the name '{}' name already exists!", name);
            return;
        }
        shaders.emplace(name, std::make_unique<Shader>(vertexShader, fragmentShader));
    }

    void ShaderManager::RemoveShader(const std::string &name) {
        if (!shaders.contains(name)) {
            logWarn("Can't delete shader because shader with the name '{}' does not exist!", name);
            return;
        }
        glDeleteProgram(shaders.at(name)->GetId());
        shaders.erase(name);
    }

    uint32_t ShaderManager::GetShader(const std::string& name) const {
        if (!shaders.contains(name)) {
            logWarn("Shader with the name '{}' does not exist!", name);
            // shaders can't have id 0
            return 0;
        }
        return shaders.at(name)->GetId();
    }
}
