#pragma once
#include <string>

namespace derelict {
enum class ShaderType {
    VertexShader,
    FragmentShader
};

class IShader {
public:
    IShader() = default;
    virtual ~IShader() = default;
    virtual uint32_t Create(const std::string& vertexShader, const std::string& fragmentShader) = 0;
    virtual void Use() const = 0;
    virtual uint32_t GetId() const = 0;
};

class Shader : public IShader {
public:
    // OpenGLShader(const std::string& vertexShader, const std::string& fragmentShader) = delete;
    OpenGLShader() = delete;

    ~OpenGLShader() = default;

    uint32_t Create(const std::string& vertexShader, const std::string& fragmentShader) override;
    // Use the shader program.
    void Use() const override;
    // Get the shader program's id.
    uint32_t GetId() const override;

private:
    // Creates a shader program given the path to the shader and shader type.
    // static uint32_t createShader(const std::string& shaderSrcPath, ShaderType shaderType);

private:
    uint32_t id;
};
}
