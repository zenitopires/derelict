#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "backend.hpp"
#include "vertex_array.hpp"
#include "shader_manager.hpp"

namespace derelict {
class Renderable {
public:
    Renderable(const glm::vec3& position, const glm::mat4& transform, std::shared_ptr<VertexArray> vao, const std::string_view& shaderName) :
    position(position), transform(transform), vao(std::move(vao)), shaderName(shaderName) {}

    glm::vec3 position;
    glm::mat4 transform;
    std::shared_ptr<VertexArray> vao;
    std::string shaderName;
};

class IRenderer {
public:
    IRenderer() = default;
    virtual ~IRenderer() = default;
    virtual void Clear() const = 0;
    virtual void Draw() const = 0;
    virtual void Submit(std::shared_ptr<Renderable> renderable) = 0;
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

    // Submits a renderable object to the rendering queue so that it can be drawn later.
    void Submit(const std::shared_ptr<Renderable> &renderable) const {
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
