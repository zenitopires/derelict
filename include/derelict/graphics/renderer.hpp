#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "vertex_array.hpp"

namespace derelict {
class Renderable {
public:
    Renderable(const glm::vec3& position, const glm::mat4& transform, std::shared_ptr<VertexArray> vao) :
    position(position), transform(transform), vao(std::move(vao)) {}

    glm::vec3 position;
    glm::mat4 transform;
    std::shared_ptr<VertexArray> vao;
};

class Renderer {
public:
    Renderer() = default;

    void Submit(std::shared_ptr<Renderable> r);
    void Clear(const glm::vec4& color) const;
    void Draw() const;

private:
    std::vector<std::shared_ptr<Renderable>> renderables;
};
}
