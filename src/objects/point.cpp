#include <ccom/objects/point.hpp>

namespace ccom::objects {

Point::Point(const ccom::geometry::AbsolutePoint& pt, char fill)
    : pt(pt)
    , fill(fill) { }

void Point::draw(ccom::Rasterizer& rast) const {
    rast.draw_point(pt, fill);
}

} // namespace ccom::objects
