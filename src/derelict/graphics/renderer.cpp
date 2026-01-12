#include <derelict/graphics/renderer.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <derelict/opengl/renderer.hpp>

namespace derelict {
void Renderer::SetAPI(GraphicsAPI api) {
    if (api == GraphicsAPI::OpenGL) {
        impl = std::make_unique<OpenGLRenderer>();
    }
}
}
