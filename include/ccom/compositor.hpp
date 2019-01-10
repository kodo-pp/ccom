#pragma once
#include <ccom/geometry.hpp>
#include <ccom/rasterizer.hpp>
#include <ccom/object.hpp>

#include <list>
#include <memory>

namespace ccom {

class Compositor {
public:
    Compositor() = default;
    Compositor(const Compositor& other) = delete;
    Compositor& operator=(const Compositor& other) = delete;
    
    void add(ccom::objects::Object* object);
    void draw(ccom::Rasterizer& rast) const;

private:
    std::list<std::shared_ptr<ccom::objects::Object>> objects;
};

Compositor& get_compositor();

} // namespace ccom
