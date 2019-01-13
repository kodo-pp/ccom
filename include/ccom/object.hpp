#pragma once
#include <ccom/rasterizer.hpp>
#include <ccom/geometry.hpp>

#include <utility>

namespace ccom::objects {

class Object {
public:
    Object() = default;
    virtual ~Object() = default;

    virtual void draw(ccom::Rasterizer& rast) const = 0;
    virtual void move(int x, int y) = 0;
};

class RotatableObject : public Object {
    virtual void rotate(
        double angle,
        ccom::geometry::AngleMeasurementUnit mu = ccom::geometry::AngleMeasurementUnit::radians
    ) = 0;
};


} // namespace ccom::objects
