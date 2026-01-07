#include <iostream>

#include <derelict/application/application.hpp>
#include <derelict/logging/logger.hpp>
#include <derelict/layer/layer.hpp>

class Game : public derelict::Application {
public:
    Game() {
        Game::GameInit();
    }

    void GameOnUpdate() override {
        std::cout << "Hello, world!\n";
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