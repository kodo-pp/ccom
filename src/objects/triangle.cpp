#include <ccom/objects/triangle.hpp>

namespace ccom::objects {

Triangle::Triangle(const ccom::geometry::AbsoluteTriangle& tri, char fill)
    : tri(tri)
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
    auto center = get_center();
    tri.a.rotate(center, angle, mu); 
    tri.b.rotate(center, angle, mu); 
    tri.c.rotate(center, angle, mu); 
}

ccom::geometry::AbsolutePoint Triangle::get_center() const {
    int sx = tri.a.x + tri.b.x + tri.c.x;
    int sy = tri.a.y + tri.b.y + tri.c.y;
    return ccom::geometry::AbsolutePoint(sx / 3, sy / 3);
}

} // namespace ccom::objects
