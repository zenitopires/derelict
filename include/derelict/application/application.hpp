#pragma once
#include <memory>
#include <derelict/window/window.hpp>
#include <derelict/graphics/renderer.hpp>

namespace derelict {
    class Application {
    public:
        Application();

        virtual ~Application();
        void Run();
        void Exit();
        virtual void GameInit() = 0;
        virtual void GameOnUpdate() = 0;
    private:
        bool appRunning = true;
        std::unique_ptr<Window> window;
    };
}
