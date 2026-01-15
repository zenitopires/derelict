#pragma once
#include <memory>
#include <map>
#include <derelict/logging/logger.hpp>
#include "shader.hpp"

namespace derelict {
// Shader Manager manages shader resources.
class ShaderManager {
public:
    ShaderManager() = default;

    void AddShader(std::unique_ptr<IShader> shader, const std::string &name);
    void AddShader(const std::string &vertexShader, const std::string &fragmentShader, const std::string &name);
    uint32_t GetShader(const std::string& name) const;

    IShader& API() const {
        if (!impl) throw std::logic_error("Renderer not initialized");
        return *impl;
    }

     std::unique_ptr<IShader> Create(const std::string& vertexShader, const std::string& fragmentShader) const {
        logDebug("Creating shader");
        return API().Create(vertexShader, fragmentShader);
    }

    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& operator=(const ShaderManager&) = delete;

    std::map<std::string, std::unique_ptr<IShader>> shaders;
    std::unique_ptr<IShader> impl;
};
}
