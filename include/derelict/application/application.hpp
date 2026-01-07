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
        virtual void GameInit() = 0;
        virtual void GameOnUpdate() = 0;
    private:
        std::unique_ptr<Window> window;
        std::unique_ptr<Renderer> renderer;
    };
}
