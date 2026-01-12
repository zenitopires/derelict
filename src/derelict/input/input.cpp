#include <derelict/input/input.hpp>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_events.h>

namespace derelict {
bool Input::KeyPressed(int keyCode) {
    SDL_PumpEvents();
    const bool* keys = SDL_GetKeyboardState(nullptr);
    if (keys[keyCode] == 1)
        return true;
    return false;
}

bool Input::MouseButtonPressed(int button)
{
    SDL_PumpEvents();
    SDL_MouseButtonFlags buttons = SDL_GetMouseState(nullptr, nullptr);
    return (buttons & button) != 0;
}
}
