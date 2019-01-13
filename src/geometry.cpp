#include <ccom/geometry.hpp>

#include <stdexcept>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

namespace ccom::geometry {

double to_radians(double angle, AngleMeasurementUnit source_mu) {
    switch (source_mu) {
    case AngleMeasurementUnit::radians:
        return angle;
    case AngleMeasurementUnit::degrees:
        return angle * M_PI / 180.0;
    default:
        throw std::out_of_range("Invalid angle measurement unit");
    }
}

double from_radians(double radians, AngleMeasurementUnit target_mu) {
    switch (target_mu) {
    case AngleMeasurementUnit::radians:
        return radians;
    case AngleMeasurementUnit::degrees:
        return radians / M_PI * 180.0;
    default:
        throw std::out_of_range("Invalid angle measurement unit");
    }
}

Point<int> relative_to_absolute_point(const Point<double>& pt, int width, int height) {
    return {
        static_cast<int>(floor(pt.x * width)),
        static_cast<int>(floor(pt.y * height)),
    };
}

} // namespace ccom::geometry
