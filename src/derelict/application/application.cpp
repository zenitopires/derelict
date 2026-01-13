#include <iostream>
#include <derelict/application/application.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <derelict/logging/logger.hpp>
#include <derelict/graphics/shader_manager.hpp>
#include <derelict/timer/timer.hpp>

namespace derelict {
Application::Application() {
    Logger::Init();
    Renderer::Init(GraphicsAPI::OpenGL);
    // Renderer::GetInstance().SetAPI(GraphicsAPI::OpenGL);

    logInfo("Initiating Derelict engine systems.");

    Props props; // Probably gonna take this in from the user at some point
    window = std::make_unique<Window>(props);

    auto& timer = Derelict::Timer::GetInstance();
    timer.Start();
}

Application::~Application() {
    logInfo("Shutting down application...");
}

void Application::Exit() {
    appRunning = false;
}


void Application::Run() {
    logInfo("Running Derelict engine.");
    appRunning = true;

    while (appRunning) {
        Derelict::Timer::GetInstance().Tick();
        GameOnUpdate();
        window->OnUpdate(appRunning);
        Renderer::GetInstance().Clear();
        Renderer::GetInstance().Draw();
    }
}
}
