#pragma once
#include <ccom/rasterizer.hpp>
#include <ccom/object.hpp>

namespace ccom::objects {

class Rectangle : public RotatableObject {
public:
    Rectangle(const ccom::geometry::AbsolutePoint& lt, const ccom::geometry::AbsolutePoint& rb, char fill);

    virtual void draw(ccom::Rasterizer& rast) const override;
    virtual void move(double x, double y) /* override */; // TODO: make doubles everywhere in the class hierarchy
    virtual void move(int x, int y) override; // stub
    virtual void rotate(
        double angle,
        ccom::geometry::AngleMeasurementUnit mu = ccom::geometry::AngleMeasurementUnit::radians
    ) override;
    virtual ccom::geometry::AbsolutePoint get_center() const;
    void update_points();

    double get_rotation() const;

private:
    double rotation = 0;
    double mx = 0, my = 0;
    ccom::geometry::AbsolutePoint o1, o2, o3, o4;
    ccom::geometry::AbsolutePoint p1, p2, p3, p4;
    char fill;
};

} // namespace ccom::objects
