#include <iostream>

#include <derelict/application/application.hpp>
#include <derelict/logging/logger.hpp>
#include <derelict/graphics/renderer.hpp>
#include <derelict/input/input.hpp>

class Game : public derelict::Application {
public:
    std::shared_ptr<derelict::Renderable> cube;

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

        cube = std::make_shared<derelict::Renderable>(position, transform, vao, "basic");
        derelict::Renderer::GetInstance().Submit(cube);
    }

    void GameOnUpdate() override {
        if (derelict::Input::GetInstance().KeyPressed(SDL_SCANCODE_A)) {
            cube->position.x += 0.01;
            derelict::Renderer::GetInstance().Submit(cube);
        }
        if (derelict::Input::GetInstance().KeyPressed(SDL_SCANCODE_D)) {
            cube->position.x -= 0.01;
            derelict::Renderer::GetInstance().Submit(cube);
        }
        if (derelict::Input::GetInstance().KeyPressed(SDL_SCANCODE_W)) {
            cube->position.y -= 0.01;
            derelict::Renderer::GetInstance().Submit(cube);
        }
        if (derelict::Input::GetInstance().KeyPressed(SDL_SCANCODE_S)) {
            cube->position.y += 0.01;
            derelict::Renderer::GetInstance().Submit(cube);
        }
        if (derelict::Input::GetInstance().KeyPressed(SDL_SCANCODE_ESCAPE)) {
            Exit();
        }
    }

    void GameInit() override {
        auto& shaderManager = derelict::ShaderManager::GetInstance();
        shaderManager.AddShader("assets/shaders/defaults/vertex.vert",
            "assets/shaders/defaults/fragment.frag", "basic");
    }
};

int main() {
    std::unique_ptr<Game> game = std::make_unique<Game>();
    game->Run();
    return 0;
}