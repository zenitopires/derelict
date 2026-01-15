#include <derelict/opengl/renderable.hpp>
#include <memory>
#include <iostream>

namespace derelict {
OpenGLRenderable::OpenGLRenderable(const float *vertices, const unsigned int *indices,
        uint32_t vertexCount, uint32_t indexCount,
        const glm::vec3& position, const glm::mat4& transform, const std::string_view& shaderName)
        : IRenderable(position, transform), shaderName(shaderName) {
        auto data = std::make_shared<Data>(vertices, indices, vertexCount, indexCount);
        vao = std::make_shared<VertexArray>(data);
}
}