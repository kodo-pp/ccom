#include <ccom/objects/point.hpp>

#include <cmath>

namespace ccom::objects {

Point::Point(const ccom::geometry::AbsolutePoint& pt, char fill)
    : pt(pt)
    , fill(fill) { }

void Point::draw(ccom::Rasterizer& rast) const {
    rast.draw_point(pt, fill);
}

void Point::move(int x, int y) {
    pt.x += x;
    pt.y += y;
}

void Point::rotate(double angle [[maybe_unused]], ccom::geometry::AngleMeasurementUnit mu [[maybe_unused]]) { }

void Point::rotate(
    const ccom::geometry::AbsolutePoint& pivot,
    double angle,
    ccom::geometry::AngleMeasurementUnit mu
) {
    auto radians = ccom::geometry::to_radians(angle, mu);
    auto nx = cos(radians) * (pt.x - pivot.x) - sin(radians) * (pt.y - pivot.y) + pivot.x;
    auto ny = cos(radians) * (pt.y - pivot.y) + sin(radians) * (pt.x - pivot.x) + pivot.y;
    pt.x = nx;
    pt.y = ny;
}

} // namespace ccom::objects
