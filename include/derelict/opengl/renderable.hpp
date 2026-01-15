#pragma once
#include <string>
#include <derelict/graphics/renderable.hpp>
#include "vertex_array.hpp"

namespace derelict {
class OpenGLRenderable : public IRenderable {
public:
    std::shared_ptr<VertexArray> vao;
    std::string shaderName;

    OpenGLRenderable(const float *vertices, const unsigned int *indices,
    uint32_t vertexCount, uint32_t indexCount,
    const glm::vec3& position, const glm::mat4& transform, const std::string_view& shaderName);
};
}
