#pragma once
#include <ccom/rasterizer.hpp>

namespace ccom::objects {

class Object {
public:
    Object() = default;
    virtual ~Object() = default;

    virtual void draw(ccom::Rasterizer& rast) const = 0;
};

} // namespace ccom::objects
