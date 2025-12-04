#pragma once

#include <string>
#include <SDL3/SDL.h>

struct Props {
    std::string title = "Derelict Engine";
    unsigned int width = 1280;
    unsigned int height = 720;
    bool vsync = true;
};

class Window {
public:
    explicit Window(const Props& props);
    ~Window();

    void OnUpdate(bool& appRunning);

    SDL_Window* GetSDLWindow() const { return window; }
    SDL_GLContext GetGLContext() const { return glContext; }
    unsigned int GetWidth()  const { return width; }
    unsigned int GetHeight() const { return height; }

private:
    void Init();
    void Shutdown();

private:
    std::string title;
    unsigned int width;
    unsigned int height;
    bool vsync;

    SDL_Window* window = nullptr;
    SDL_GLContext glContext = nullptr;
    SDL_Event m_Event;
};
