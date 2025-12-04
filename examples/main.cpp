#include <iostream>

#include <derelict/application/application.hpp>
#include <derelict/logging/logger.hpp>

int main() {
    derelict::Logger::Init();
    logInfo("Starting Derelict engine");
    std::unique_ptr<derelict::Application> app = std::make_unique<derelict::Application>();
    app->Run();
    return 0;
}