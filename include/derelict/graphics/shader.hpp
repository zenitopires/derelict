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
    void Use();
    void Unuse();
    uint32_t GetId();

private:
    static uint32_t createShader(const std::string& shaderSrcPath, ShaderType shaderType);

private:
    uint32_t id;
};
}

