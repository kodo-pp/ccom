#include <ccom/util.hpp>
#include <ccom/rasterizer.hpp>
#include <ccom/compositor.hpp>
#include <ccom/geometry.hpp>
#include <ccom/objects/triangle.hpp>

#include <iostream>
#include <iomanip>
#include <cmath>
#include <unistd.h>

int main() {
    std::cout.sync_with_stdio(false);
    std::cin.tie(nullptr);

    const int width = 60, height = 40;

    auto& rast = ccom::get_rasterizer();
    auto& comp = ccom::get_compositor();

    auto tri = new ccom::objects::Triangle(
        ccom::geometry::AbsoluteTriangle(
            {10, 10},
            {60, 30},
            {15, 30}), 
        '#'
    );
    comp.add(tri);

    rast.set_buffer_size(width, height, ':');

    double angle = 0;
    while (true) {
        rast.clear_buffer(':');
        tri->rotate(-10.0, ccom::geometry::AngleMeasurementUnit::degrees);
        comp.draw(rast);
        rast.flush_buffer(std::cout);
        usleep(1000000 / 1);
    };
}
