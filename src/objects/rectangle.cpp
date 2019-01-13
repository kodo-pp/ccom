#include <ccom/objects/rectangle.hpp>
#include <cmath>

namespace ccom::objects {

Rectangle::Rectangle(const ccom::geometry::AbsolutePoint& lt, const ccom::geometry::AbsolutePoint& rb, char fill)
    : o1(lt.x, rb.y)
    , o2(lt.x, lt.y)
    , o3(rb.x, lt.y)
    , o4(rb.x, rb.y)
    , p1(o1)
    , p2(o2)
    , p3(o3)
    , p4(o4)
    , fill(fill) { }


void Rectangle::draw(ccom::Rasterizer& rast) const {
    rast.fill_triangle(ccom::geometry::AbsoluteTriangle(p1, p2, p3), fill);
    rast.fill_triangle(ccom::geometry::AbsoluteTriangle(p1, p4, p3), fill);
}

void Rectangle::update_points() {
    p1.x = round(o1.x + mx);
    p1.y = round(o1.y + my);
    p2.x = round(o2.x + mx);
    p2.y = round(o2.y + my);
    p3.x = round(o3.x + mx);
    p3.y = round(o3.y + my);
    p4.x = round(o4.x + mx);
    p4.y = round(o4.y + my);

    auto center = get_center();
    p1.rotate(center, rotation, ccom::geometry::AngleMeasurementUnit::radians);
    p2.rotate(center, rotation, ccom::geometry::AngleMeasurementUnit::radians);
    p3.rotate(center, rotation, ccom::geometry::AngleMeasurementUnit::radians);
    p4.rotate(center, rotation, ccom::geometry::AngleMeasurementUnit::radians);
}


void Rectangle::move(double x, double y) {
    // TODO: PLEASE DELETE THIS SHIT
    mx += x;
    my += y;
    update_points();
}

void Rectangle::move(int x, int y) {
    move(double(x), double(y));
}

double Rectangle::get_rotation() const {
    return rotation;
}

void Rectangle::rotate(double angle, ccom::geometry::AngleMeasurementUnit mu) {
    p1 = o1;
    p2 = o2;
    p3 = o3;
    p4 = o4;
    rotation += ccom::geometry::to_radians(angle, mu);
    update_points();
}

ccom::geometry::AbsolutePoint Rectangle::get_center() const {
    return ccom::geometry::AbsolutePoint((o1.x + o3.x)/2 + round(mx), (o1.y + o3.y)/2 + round(my));
}

} // namespace ccom::objects
