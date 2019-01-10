#pragma once
#include <ccom/rasterizer.hpp>
#include <ccom/object.hpp>

namespace ccom::objects {

class Point : public Object {
public:
    Point(const ccom::geometry::AbsolutePoint& pt, char fill);

    virtual void draw(ccom::Rasterizer& rast) const override;

private:
    ccom::geometry::AbsolutePoint pt;
    char fill;
};

} // namespace ccom::objects
