#include <derelict/graphics/renderer.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <derelict/graphics/shader_manager.hpp>
#include <glad/glad.h>

namespace derelict {
    void Renderer::Submit(std::shared_ptr<Renderable> renderable) {
        renderables.push_back(std::move(renderable));
    }

    void Renderer::Clear(const glm::vec4 &color) const {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::Draw() const {
        for (const std::shared_ptr<Renderable>& renderable : renderables) {
            renderable->vao->Bind();
            glUseProgram(ShaderManager::GetInstance().GetShader(renderable->shaderName));
            glUniformMatrix4fv(glGetUniformLocation(ShaderManager::GetInstance().GetShader(renderable->shaderName), "transform"), 1, GL_FALSE, glm::value_ptr(renderable->transform));
            glUniform3fv(glGetUniformLocation(ShaderManager::GetInstance().GetShader(renderable->shaderName), "position"), 1, glm::value_ptr(renderable->position));
            glDrawElements(GL_TRIANGLES, renderable->vao->GetIndexCount(), GL_UNSIGNED_INT, 0);
            renderable->vao->Unbind();
        }
    }
}
