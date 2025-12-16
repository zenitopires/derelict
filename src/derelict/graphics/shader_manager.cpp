#include <derelict/graphics/shader_manager.hpp>

namespace derelict {
    void ShaderManager::AddShader(std::shared_ptr<Shader> shader, const std::string &name) {
        shaders.emplace(name, shader);
    }

    void ShaderManager::AddShader(const std::string &vertexShader, const std::string &fragmentShader, const std::string& name) {
        auto shader = std::make_shared<Shader>(vertexShader, fragmentShader);
        shaders.emplace(name, shader);
    }

    void ShaderManager::RemoveShader(const std::string &name) {
        shaders.erase(name);
    }

    uint32_t ShaderManager::GetShader(const std::string& name) const {
        return shaders.at(name)->GetId();
    }


}