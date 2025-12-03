#include "renderer.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace derelict {
    void Renderer::Submit(std::shared_ptr<Renderable> renderable) {
        renderables.push_back(std::move(renderable));
    }

    void Renderer::Clear(const glm::vec4 &color) {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::Draw() {
        for (auto renderable : renderables) {
            renderable->vao->Bind();
            // glGetUniformLocation(shader, name);
            glUniformMatrix4fv(glGetUniformLocation(renderable->vao->GetShaderId(), "transform"), 1, GL_FALSE, glm::value_ptr(renderable->transform));
            glUniform3fv(glGetUniformLocation(renderable->vao->GetShaderId(), "position"), 1, glm::value_ptr(renderable->position));
            glDrawElements(GL_TRIANGLES, renderable->vao->GetIndexCount(), GL_UNSIGNED_INT, 0);
            renderable->vao->Unbind();
        }
    }
}
