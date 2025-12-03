#include "application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "src/logging/logger.hpp"

namespace derelict {

Application::Application() {
    logInfo("Running application!");

    Props props; // Probably gonna take this in from the user at some point
    window = std::make_unique<Window>(props);
    renderer = std::make_unique<Renderer>();
}

Application::~Application() {
    logInfo("Shutting down application...");
}

void Application::Run() {
    bool appRunning = true;

    // Temporary data, this would get moved out to some sort of scene reader eventually
    float vertices[] = {
         0.5f,  0.5f, 0.0f,   1, 0, 0,
         0.5f, -0.5f, 0.0f,   0, 1, 0,
        -0.5f, -0.5f, 0.0f,   0, 0, 1,
        -0.5f,  0.5f, 0.0f,   0.5, 0.5, 0.5
    };

    unsigned int indices[] = { 0, 1, 3, 1, 2, 3 };

    auto data = std::make_shared<Data>(vertices, indices, sizeof(vertices), sizeof(indices));

    auto vao = std::make_shared<VertexArray>(data);

    glm::mat4 transform(1.0f);
    glm::vec3 position(0.0f, 0.0f, 0.0f);

    auto cube = std::make_shared<Renderable>(position, transform, vao);
    renderer->Submit(cube);

    glm::vec4 clearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (appRunning) {
        window->OnUpdate(appRunning);
        renderer->Clear(clearColor);
        renderer->Draw();
    }
}
}
