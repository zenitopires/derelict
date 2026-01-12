#pragma once

namespace derelict {
class Input {
public:
    Input() = default;

    static Input& GetInstance() {
        static Input instance;
        return instance;
    }

    bool KeyPressed(int keyCode);
    bool MouseButtonPressed(int button);
};
}