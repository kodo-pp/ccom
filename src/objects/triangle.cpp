#include <ccom/objects/triangle.hpp>

namespace ccom::objects {

Triangle::Triangle(const ccom::geometry::AbsoluteTriangle& tri, char fill)
    : tri(tri)
    , orig_tri(tri)
    , fill(fill) { }

void Triangle::draw(ccom::Rasterizer& rast) const {
    rast.fill_triangle(tri, fill);
}

void Triangle::move(int x, int y) {
    // TODO: make this shit not shitty
    tri.a.x += x;
    tri.a.y += y;
    tri.b.x += x;
    tri.b.x += x;
    tri.c.y += y;
    tri.c.y += y;
}

void Triangle::rotate(double angle, ccom::geometry::AngleMeasurementUnit mu) {
    // TODO: rotate the original triangle and save it into the second one (store 2 triangles)
    tri = orig_tri;
    auto center = get_center();
    auto radians = ccom::geometry::to_radians(angle, mu) + rotation;
    tri.a.rotate(center, radians, ccom::geometry::AngleMeasurementUnit::radians); 
    tri.b.rotate(center, radians, ccom::geometry::AngleMeasurementUnit::radians); 
    tri.c.rotate(center, radians, ccom::geometry::AngleMeasurementUnit::radians); 
    rotation = radians;
}

ccom::geometry::AbsolutePoint Triangle::get_center() const {
    int sx = tri.a.x + tri.b.x + tri.c.x;
    int sy = tri.a.y + tri.b.y + tri.c.y;
    return ccom::geometry::AbsolutePoint(sx / 3, sy / 3);
}

} // namespace ccom::objects
