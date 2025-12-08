#pragma once
#include <string>

namespace derelict {
enum class ShaderType {
    VertexShader,
    FragmentShader
};

class Shader {
public:
    Shader(const std::string& vertexShader, const std::string& fragmentShader);
    ~Shader();
    // Use the shader program.
    void Use() const;
    // Unuse the shader program.
    void Unuse() const;
    // Get the shader program's id.
    uint32_t GetId() const;

private:
    // Creates a shader program given the path to the vertex and fragment shaders.
    static uint32_t createShader(const std::string& shaderSrcPath, ShaderType shaderType);

private:
    uint32_t id;
};
}

