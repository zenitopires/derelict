#pragma once
#include <derelict/graphics/renderer.hpp>
#include <derelict/graphics/renderable.hpp>

namespace derelict {
class OpenGLRenderer : public IRenderer {
public:
    OpenGLRenderer() = default;
    void Draw() const override;
    void Clear() const override;
    void Submit(std::shared_ptr<IRenderable> renderable) override;
    std::shared_ptr<IRenderable> CreateRenderable(const float* vertices, const unsigned int* indices,
        uint32_t vertexCount, uint32_t indexCount, const glm::vec3& position, const glm::mat4& transform,
        std::string_view shaderName) override;

private:
    std::vector<std::shared_ptr<IRenderable>> renderables{};
};
}
