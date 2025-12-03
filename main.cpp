#include <iostream>

#include "src/application/application.hpp"
#include "src/logging/logger.hpp"

int main() {
    derelict::Logger::Init();
    logInfo("Starting Derelict engine");
    // derelict::Logger::LOG_INFO("Starting Derelict engine");
    std::unique_ptr<derelict::Application> app = std::make_unique<derelict::Application>();
    app->Run();
    return 0;
}