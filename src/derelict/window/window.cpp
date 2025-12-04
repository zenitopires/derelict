#include <derelict/window/window.hpp>

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <derelict/logging/logger.hpp>

bool s_SDLInitialized = false;

Window::Window(const Props& props)
    : title(props.title),
      width(props.width),
      height(props.height),
      vsync(props.vsync)
{
    Init();
}

Window::~Window() {
    if (window) SDL_DestroyWindow(window);

    if (s_SDLInitialized) {
        SDL_Quit();
        s_SDLInitialized = false;
    }
}

void Window::Init() {
    if (!s_SDLInitialized) {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            logError("Failed to initialize SDL: {}", SDL_GetError());
            std::exit(-1);
        }
        s_SDLInitialized = true;
    }

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow(
        title.c_str(),
        width,
        height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        logError("Failed to create SDL window: {}", SDL_GetError());
        SDL_Quit();
        std::exit(-1);
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        logError("Failed to create OpenGL context: {}", SDL_GetError());
        SDL_Quit();
        std::exit(-1);
    }

    if (!SDL_GL_MakeCurrent(window, glContext)) {
        logError("Failed to setup an OpenGL context!");
    }

    if (!SDL_GL_SetSwapInterval(vsync ? 1 : 0)) {
        logError("Failed to set swap interval for the OpenGL context!");
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        logError("Failed to initialize GLAD");
        SDL_Quit();
        std::exit(-1);
    }

    logDebug("Window initialized: {} ({} x {})", title.c_str(), width, height);
}

void Window::OnUpdate(bool& appRunning) {
    SDL_GL_SwapWindow(window);

    while (SDL_PollEvent(&m_Event)) {

        switch (m_Event.type) {

        case SDL_EVENT_QUIT:
            appRunning = false;
            break;

        case SDL_EVENT_WINDOW_RESIZED: {
            unsigned int newWidth  = m_Event.window.data1;
            unsigned int newHeight = m_Event.window.data2;

            logDebug("Window resized: {} x {}", newWidth, newHeight);

            width  = newWidth;
            height = newHeight;

            glViewport(0, 0, width, height);
            break;
        }

        case SDL_EVENT_WINDOW_MINIMIZED:
            break;

        case SDL_EVENT_WINDOW_MAXIMIZED:
            break;
        }
    }
}
