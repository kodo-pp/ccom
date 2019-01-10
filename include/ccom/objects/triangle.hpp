#pragma once
#include <ccom/rasterizer.hpp>
#include <ccom/object.hpp>

namespace ccom::objects {

class Triangle : public Object {
public:
    Triangle(const ccom::geometry::AbsoluteTriangle& tri, char fill);

    virtual void draw(ccom::Rasterizer& rast) const override;

private:
    ccom::geometry::AbsoluteTriangle tri;
    char fill;
};

} // namespace ccom::objects
