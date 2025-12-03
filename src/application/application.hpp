#pragma once
#include <memory>
#include "src/window/window.hpp"
#include "src/graphics/renderer.hpp"

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
