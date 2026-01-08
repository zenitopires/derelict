#include <iostream>

#include <derelict/application/application.hpp>
#include <derelict/logging/logger.hpp>
#include <derelict/layer/layer.hpp>
#include <derelict/graphics/renderer.hpp>

class Game : public derelict::Application {
public:
    Game() {
        Game::GameInit();
        glm::vec4 clearColor(0.2f, 0.3f, 0.3f, 1.0f);
        derelict::Renderer::GetInstance().SetClearColor(clearColor);
        derelict::Renderer::GetInstance().Clear();

        float vertices[] = {
            0.5f,  0.5f, 0.0f,   1, 0, 0,
            0.5f, -0.5f, 0.0f,   0, 1, 0,
           -0.5f, -0.5f, 0.0f,   0, 0, 1,
           -0.5f,  0.5f, 0.0f,   0.5, 0.5, 0.5
       };

        unsigned int indices[] = { 0, 1, 3, 1, 2, 3 };

        auto data = std::make_shared<derelict::Data>(vertices, indices, sizeof(vertices), sizeof(indices));

        auto vao = std::make_shared<derelict::VertexArray>(data);

        glm::mat4 transform(1.0f);
        glm::vec3 position(0.0f, 0.0f, 0.0f);

        auto cube = std::make_shared<derelict::Renderable>(position, transform, vao, "basic");
        derelict::Renderer::GetInstance().Submit(cube);
    }

    void GameOnUpdate() override {
    }

    void GameInit() override {
        auto& shaderManager = derelict::ShaderManager::GetInstance();
        shaderManager.AddShader("assets/shaders/defaults/vertex.vert",
            "assets/shaders/defaults/fragment.frag", "basic");
    }
};

int main() {
    derelict::Logger::Init();
    logInfo("Starting Derelict engine");
    std::unique_ptr<Game> game = std::make_unique<Game>();

    game->Run();
    return 0;
}