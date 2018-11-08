#include <ccom/geometry.hpp>

namespace ccom {

Point<int> relative_to_absolute_point(const Point<double>& pt, int width, int height) {
    return {
        static_cast<int>(floor(pt.x * width)),
        static_cast<int>(floor(pt.y * height)),
    };
}

} // namespace ccom
