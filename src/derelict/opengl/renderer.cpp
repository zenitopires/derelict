#include <derelict/opengl/renderer.hpp>
#include <glad/glad.h>

#include "glm/gtc/type_ptr.hpp"

namespace derelict {
void OpenGLRenderer::Submit(std::shared_ptr<Renderable> renderable) {
    renderables.push_back(std::move(renderable));
}

void OpenGLRenderer::Clear() const {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::Draw() const {
    for (const std::shared_ptr<Renderable>& renderable : renderables) {
        renderable->vao->Bind();
        // Renderer::GetInstance().GetShaderManager().GetShader()
        glUseProgram(Renderer::GetInstance().GetShaderManager().GetShader(renderable->shaderName));
        glUniformMatrix4fv(glGetUniformLocation(Renderer::GetInstance().GetShaderManager().GetShader(renderable->shaderName), "transform"), 1, GL_FALSE, glm::value_ptr(renderable->transform));
        glUniform3fv(glGetUniformLocation(Renderer::GetInstance().GetShaderManager().GetShader(renderable->shaderName), "position"), 1, glm::value_ptr(renderable->position));
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(renderable->vao->GetIndexCount()), GL_UNSIGNED_INT, 0);
        renderable->vao->Unbind();
    }
}
}
