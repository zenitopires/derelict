#include <derelict/graphics/renderer.hpp>

namespace derelict {
class OpenGLRenderer : public IRenderer {
public:
    OpenGLRenderer() = default;
    void Draw() const override;
    void Clear() const override;
    void Submit(std::shared_ptr<Renderable> renderable) override;
private:
    std::vector<std::shared_ptr<Renderable>> renderables;
};
}
