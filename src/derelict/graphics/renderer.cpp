#include <derelict/graphics/renderer.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <derelict/opengl/renderer.hpp>

#include "derelict/opengl/shader.hpp"

std::unique_ptr<derelict::Renderer> derelict::Renderer::rendererInst = nullptr;
std::unique_ptr<derelict::ShaderManager> derelict::Renderer::shaderManagerInst = nullptr;

namespace derelict {
void Renderer::Init(GraphicsAPI api) {
    if (rendererInst != nullptr && rendererInst->impl) throw std::logic_error("Renderer already initialized.");

    rendererInst = std::make_unique<Renderer>();
    shaderManagerInst = std::make_unique<ShaderManager>();

    switch (api) {
        case GraphicsAPI::OpenGL:
            rendererInst->impl = std::make_unique<OpenGLRenderer>();
            // Initialize ShaderManager as well
            shaderManagerInst->impl = std::make_unique<OpenGLShader>();
            break;
        default:
            throw std::logic_error("API is not supported! Only OpenGL is supported!");
    }
}
}
