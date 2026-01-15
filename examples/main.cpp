#include <iostream>

#include <derelict/application/application.hpp>
#include <derelict/logging/logger.hpp>
#include <derelict/graphics/renderer.hpp>
#include <derelict/input/input.hpp>

#include "derelict/opengl/renderable.hpp"

class Game : public derelict::Application {
public:
    std::shared_ptr<derelict::IRenderable> cube;

    Game() {
        Game::GameInit();

        float vertices[] = {
            0.5f,  0.5f, 0.0f,   1, 0, 0,
            0.5f, -0.5f, 0.0f,   0, 1, 0,
           -0.5f, -0.5f, 0.0f,   0, 0, 1,
           -0.5f,  0.5f, 0.0f,   0.5, 0.5, 0.5
       };

        unsigned int indices[] = { 0, 1, 3, 1, 2, 3 };

        glm::mat4 transform(1.0f);
        glm::vec3 position(0.0f, 0.0f, 0.0f);

        cube = derelict::Renderer::GetInstance().CreateRenderable(vertices, indices, sizeof(vertices), sizeof(indices), position, transform, "basic");

        derelict::Renderer::GetInstance().Submit(cube);
    }

    void GameOnUpdate() override {
        if (derelict::Input::GetInstance().KeyPressed(SDL_SCANCODE_A)) {
            auto pos = cube->GetPosition();
            pos.x += 0.01;
            cube->SetPosition(pos);
            derelict::Renderer::GetInstance().Submit(cube);
        }
        if (derelict::Input::GetInstance().KeyPressed(SDL_SCANCODE_D)) {
            auto pos = cube->GetPosition();
            pos.x -= 0.01;
            cube->SetPosition(pos);
            derelict::Renderer::GetInstance().Submit(cube);
        }
        if (derelict::Input::GetInstance().KeyPressed(SDL_SCANCODE_W)) {
            auto pos = cube->GetPosition();
            pos.y -= 0.01;
            cube->SetPosition(pos);
            derelict::Renderer::GetInstance().Submit(cube);
        }
        if (derelict::Input::GetInstance().KeyPressed(SDL_SCANCODE_S)) {
            auto pos = cube->GetPosition();
            pos.y += 0.01;
            cube->SetPosition(pos);
            derelict::Renderer::GetInstance().Submit(cube);
        }
        if (derelict::Input::GetInstance().KeyPressed(SDL_SCANCODE_ESCAPE)) {
            Exit();
        }
    }

    void GameInit() override {
        derelict::Renderer::GetInstance().GetShaderManager().AddShader("assets/shaders/defaults/vertex.vert",
            "assets/shaders/defaults/fragment.frag", "basic");
    }
};

int main() {
    std::unique_ptr<Game> game = std::make_unique<Game>();
    game->Run();
    return 0;
}