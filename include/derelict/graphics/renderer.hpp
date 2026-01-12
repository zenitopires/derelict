#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
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

class Renderer {
public:
    Renderer() = default;

    static Renderer& GetInstance() {
        static Renderer instance;
        return instance;
    }

    // Set clear color.
    void SetClearColor(const glm::vec4& color);
    // Submits a renderable object to the rendering queue so that it can be drawn later.
    void Submit(std::shared_ptr<Renderable> renderable);
    // Specify color to be used by glClear().
    void Clear() const;
    // Draw the objects that were submitted to the rendering queue.
    void Draw() const;
private:
    std::vector<std::shared_ptr<Renderable>> renderables;
    glm::vec4 clearColor;
};
}
