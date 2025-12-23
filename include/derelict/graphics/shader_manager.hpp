#pragma once
#include <memory>
#include <map>
#include "shader.hpp"

namespace derelict {
// Shader Manager manages shader resources.
class ShaderManager {
public:
    void AddShader(std::unique_ptr<Shader> shader, const std::string &name);
    void AddShader(const std::string &vertexShader, const std::string &fragmentShader, const std::string &name);
    void RemoveShader(const std::string& name);
    uint32_t GetShader(const std::string& name) const;

    static ShaderManager& GetInstance() {
        static ShaderManager instance;
        return instance;
    }

    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& operator=(const ShaderManager&) = delete;
private:
    ShaderManager() = default;
    std::map<std::string, std::unique_ptr<Shader>> shaders;
};
}
