#pragma once

class Layer {
public:
    Layer() = default;
    virtual ~Layer() = default;
    virtual void OnUpdate() = 0;
};