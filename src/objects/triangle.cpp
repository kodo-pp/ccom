#include <ccom/objects/triangle.hpp>

namespace ccom::objects {

Triangle::Triangle(const ccom::geometry::AbsoluteTriangle& tri, char fill)
    : tri(tri)
    , fill(fill) { }

void Triangle::draw(ccom::Rasterizer& rast) const {
    rast.fill_triangle(tri, fill);
}

} // namespace ccom::objects
