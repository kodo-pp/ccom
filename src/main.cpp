#include <ccom/util.hpp>
#include <ccom/draw_manager.hpp>

#include <iostream>
#include <cmath>
#include <unistd.h>

int main() {
    std::cout.sync_with_stdio(false);
    std::cin.tie(nullptr);

    const int width = 120, height = 40;
    
    auto& draw = ccom::get_draw_manager();
    draw.set_buffer_size(width, height, '.');

    auto get_delta = [](double angle) {
        int offset_x = cos(angle) * 30;
        int offset_y = sin(angle) * 15;
        return std::make_pair(60 + offset_x, 20 + offset_y);
    };
    
    double angle = 0;
    while (true) {
        auto v1 = get_delta(angle);
        auto v2 = get_delta(angle + 2 * M_PI / 3);
        auto v3 = get_delta(angle - 2 * M_PI / 3);
        draw.fill_triangle(v1, v2, v3, '#');
        draw.flush_buffer(std::cout);
        draw.clear_buffer('.');
        usleep(1'000'000 / 30);
        angle += 1.0 / 30.0;
    }
}
