#include <ccom/compositor.hpp>

namespace ccom {

void Compositor::add(ccom::objects::Object* object) {
    objects.push_back(std::shared_ptr<ccom::objects::Object>(object));
}

void Compositor::draw(ccom::Rasterizer& rast) const {
    for (const auto& obj_ptr : objects) {
        obj_ptr.get()->draw(rast);
    }
}

Compositor& get_compositor() {
    static Compositor compositor;
    return compositor;
}

} // namespace ccom
