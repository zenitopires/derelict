#pragma once
#include <memory>
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
    virtual std::unique_ptr<IShader> Create(const std::string& vertexShader, const std::string& fragmentShader) = 0;
    virtual void Use() const = 0;
    virtual uint32_t GetId() const = 0;
};
}
