#pragma once
#include <vector>
#include <memory>
#include "backend.hpp"
#include "shader_manager.hpp"
#include "renderable.hpp"

namespace derelict {
class IRenderer {
public:
    IRenderer() = default;
    virtual ~IRenderer() = default;
    virtual void Clear() const = 0;
    virtual void Draw() const = 0;
    virtual std::shared_ptr<IRenderable> CreateRenderable(const float* vertices, const unsigned int* indices,
      uint32_t vertexCount, uint32_t indexCount, const glm::vec3& position, const glm::mat4& transform,
      std::string_view shaderName) = 0;
    virtual void Submit(std::shared_ptr<IRenderable> renderable) = 0;
};

class Renderer {
public:
    Renderer() = default;

    static void Init(GraphicsAPI api);

    static Renderer& GetInstance() {
        return *rendererInst;
    }

    static ShaderManager& GetShaderManager() {
        return *shaderManagerInst;
    }

    IRenderer& API() const {
        if (!impl) throw std::logic_error("Renderer not initialized");
        return *impl;
    }

    std::shared_ptr<IRenderable> CreateRenderable(const float *vertices, const unsigned int *indices,
        const uint32_t vertexCount, const uint32_t indexCount,
        const glm::vec3& position, const glm::mat4& transform, const std::string_view& shaderName) const {
        return API().CreateRenderable(vertices, indices, vertexCount, indexCount, position, transform, shaderName);
    }

    // Submits a renderable object to the rendering queue so that it can be drawn later.
    void Submit(const std::shared_ptr<IRenderable> &renderable) const {
        API().Submit(renderable);
    }
    // Specify color to be used by glClear().
    void Clear() const {
        API().Clear();
    }
    // Draw the objects that were submitted to the rendering queue.
    void Draw() const {
        API().Draw();
    }

    static std::unique_ptr<Renderer> rendererInst;
    static std::unique_ptr<ShaderManager> shaderManagerInst;
private:
    std::unique_ptr<IRenderer> impl;
};
}
