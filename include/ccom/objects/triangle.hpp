#pragma once
#include <ccom/rasterizer.hpp>
#include <ccom/object.hpp>

namespace ccom::objects {

class Triangle : public RotatableObject {
public:
    Triangle(const ccom::geometry::AbsoluteTriangle& tri, char fill);

    virtual void draw(ccom::Rasterizer& rast) const override;
    virtual void move(int x, int y) override;
    virtual void rotate(
        double angle,
        ccom::geometry::AngleMeasurementUnit mu = ccom::geometry::AngleMeasurementUnit::radians
    ) override;
    virtual ccom::geometry::AbsolutePoint get_center() const;

private:
    double rotation = 0;
    ccom::geometry::AbsoluteTriangle tri;
    ccom::geometry::AbsoluteTriangle orig_tri;
    char fill;
};

} // namespace ccom::objects
