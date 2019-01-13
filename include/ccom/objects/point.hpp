#pragma once
#include <ccom/rasterizer.hpp>
#include <ccom/object.hpp>

namespace ccom::objects {

class Point : public RotatableObject {
public:
    Point(const ccom::geometry::AbsolutePoint& pt, char fill);

    virtual void draw(ccom::Rasterizer& rast) const override;
    virtual void move(int x, int y) override;
    virtual void rotate(
        double angle,
        ccom::geometry::AngleMeasurementUnit mu = ccom::geometry::AngleMeasurementUnit::radians
    ) override;
    virtual void rotate(
        const ccom::geometry::AbsolutePoint& pivot,
        double angle,
        ccom::geometry::AngleMeasurementUnit mu = ccom::geometry::AngleMeasurementUnit::radians
    );

private:
    ccom::geometry::AbsolutePoint pt;
    char fill;
};

} // namespace ccom::objects
