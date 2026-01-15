#pragma once
#include <glm/glm.hpp>

namespace derelict {
class IRenderable {
public:
    IRenderable(const glm::vec3& position,
                const glm::mat4& transform)
        : position(position), transform(transform) {}
    virtual ~IRenderable() = default;

    void SetPosition(const glm::vec3& p) { position = p; }
    const glm::vec3& GetPosition() const { return position; }
    void SetTransform(const glm::mat4& t) { transform = t; }
    const glm::mat4& GetTransform() const { return transform; }

protected:
    glm::vec3 position;
    glm::mat4 transform;
};
}