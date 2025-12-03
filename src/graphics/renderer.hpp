#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "vertex_array.hpp"

namespace derelict {
class Renderable {
public:
    Renderable(glm::vec3 position, glm::mat4 transform, std::shared_ptr<VertexArray> vao) :
    position(position), transform(transform), vao(std::move(vao)) {}

    glm::vec3 position;
    glm::mat4 transform;
    std::shared_ptr<VertexArray> vao;
};

class Renderer {
public:
    Renderer() = default;

    void Submit(std::shared_ptr<Renderable> r);
    void Clear(const glm::vec4& color);
    void Draw();

private:
    std::vector<std::shared_ptr<Renderable>> renderables;
};
}
