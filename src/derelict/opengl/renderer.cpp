#include <derelict/opengl/renderer.hpp>
#include <glad/glad.h>
#include <derelict/opengl/renderable.hpp>
#include "glm/gtc/type_ptr.hpp"

namespace derelict {

std::shared_ptr<IRenderable> OpenGLRenderer::CreateRenderable(const float* vertices, const unsigned int* indices,
   uint32_t vertexCount, uint32_t indexCount, const glm::vec3& position, const glm::mat4& transform,
   std::string_view shaderName) {
    return std::make_shared<OpenGLRenderable>(vertices, indices, vertexCount, indexCount, position, transform, shaderName);
}

void OpenGLRenderer::Submit(std::shared_ptr<IRenderable> renderable) {
    renderables.push_back(std::move(renderable));
}

void OpenGLRenderer::Clear() const {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::Draw() const {
    for (const std::shared_ptr<IRenderable>& r : renderables) {
        auto renderable = std::static_pointer_cast<OpenGLRenderable>(r);
        renderable->vao->Bind();
        glUseProgram(derelict::Renderer::GetShaderManager().GetShader(renderable->shaderName));
        glUniformMatrix4fv(glGetUniformLocation(derelict::Renderer::GetInstance().GetShaderManager().GetShader(renderable->shaderName), "transform"), 1, GL_FALSE, glm::value_ptr(renderable->GetTransform()));
        glUniform3fv(glGetUniformLocation(derelict::Renderer::GetInstance().GetShaderManager().GetShader(renderable->shaderName), "position"), 1, glm::value_ptr(renderable->GetPosition()));
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(renderable->vao->GetIndexCount()), GL_UNSIGNED_INT, 0);
        renderable->vao->Unbind();
    }
}
}
