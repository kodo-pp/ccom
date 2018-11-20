#include <ccom/util.hpp>
#include <ccom/rasterizer.hpp>
#include <ccom/geometry.hpp>

#include <iostream>
#include <iomanip>
#include <cmath>
#include <unistd.h>

int main() {
    std::cout.sync_with_stdio(false);
    std::cin.tie(nullptr);

    const int width = 120, height = 40;

    auto get_delta = [](double angle) {
        int offset_x = cos(angle) * 30;
        int offset_y = sin(angle) * 15 / 2;
        return ccom::geometry::AbsolutePoint(60 + offset_x, 20 + offset_y);
    };

    auto get_triangle = [&](double angle) {
        return ccom::geometry::AbsoluteTriangle(
            get_delta(angle),
            get_delta(angle + 2 * M_PI / 3),
            get_delta(angle - 2 * M_PI / 3)
        );
    };
    
    auto& raster = ccom::get_rasterizer();
    raster.set_buffer_size(width, height, ':');
    double angle = 0;
    while (true) {
        auto tri = get_triangle(angle);
        raster.fill_triangle(tri, '=');
        raster.draw_line(ccom::geometry::AbsoluteLine({15, 19}, tri.a), ' ');
        raster.draw_line(ccom::geometry::AbsoluteLine({15, 19}, tri.b), ' ');
        raster.draw_line(ccom::geometry::AbsoluteLine({15, 19}, tri.c), ' ');
        raster.draw_line(ccom::geometry::AbsoluteLine({30, 10}, tri.a), '@');
        raster.draw_line(ccom::geometry::AbsoluteLine({30, 10}, tri.b), '@');
        raster.draw_line(ccom::geometry::AbsoluteLine({30, 10}, tri.c), '@');

        raster.flush_buffer(std::cout);
        raster.clear_buffer(':');
        angle += 1.0 / 60.0;
        usleep(1000000 / 60);
    };
}
