#include <ccom/util.hpp>
#include <ccom/rasterizer.hpp>
#include <ccom/compositor.hpp>
#include <ccom/geometry.hpp>
#include <ccom/objects/triangle.hpp>
#include <ccom/objects/rectangle.hpp>

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

    auto rect = new ccom::objects::Rectangle(
        {10, 10},
        {15, 20}, 
        'o'
    );
    comp.add(rect);

    rast.set_buffer_size(width, height, '.');

    while (true) {
        rast.clear_buffer('.');
        rect->rotate(-2, ccom::geometry::AngleMeasurementUnit::degrees);
        auto angle = rect->get_rotation();
        rect->move(sin(-angle) * 0.3, cos(-angle) * 0.3);
        comp.draw(rast);
        rast.flush_buffer(std::cout);
        usleep(1000000 / 60);
    };
}
