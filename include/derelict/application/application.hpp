#pragma once
#include <memory>
#include "../window/window.hpp"
#include "../graphics/renderer.hpp"

namespace derelict {
    class Application {
    public:
        Application();
        ~Application();
        void Run();
    private:
        std::unique_ptr<Window> window;
        std::unique_ptr<Renderer> renderer;
    };
}
