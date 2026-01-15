#pragma once
#include <derelict/graphics/shader.hpp>

namespace derelict {
class OpenGLShader : public IShader {
public:
    OpenGLShader(const uint32_t id) : id(id) {}
    OpenGLShader() = default;

    std::unique_ptr<IShader> Create(const std::string& vertexShader, const std::string& fragmentShader) override;

    static uint32_t CreateShader(const std::string& shaderSrcPath, ShaderType shaderType);

    ~OpenGLShader() override;

    // Use the shader program.
    void Use() const override;
    // Get the shader program's id.
    uint32_t GetId() const override;

private:
    uint32_t id;
};
}