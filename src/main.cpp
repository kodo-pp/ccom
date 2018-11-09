#include <ccom/util.hpp>
#include <ccom/draw_manager.hpp>
#include <ccom/draw_loop_manager.hpp>
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
        return ccom::AbsolutePoint(60 + offset_x, 20 + offset_y);
    };

    auto get_triangle = [&](double angle) {
        return ccom::AbsoluteTriangle(
            get_delta(angle),
            get_delta(angle + 2 * M_PI / 3),
            get_delta(angle - 2 * M_PI / 3)
        );
    };
    
    auto& draw = ccom::get_draw_manager();
    draw.set_buffer_size(width, height, ':');
    auto& draw_loop = ccom::get_draw_loop_manager();
    draw_loop.set_max_fps(30);
    
    double angle = 0;
    draw_loop.run_draw_loop([&](double fps, double elapsed_time, double frame_time) {
        auto tri = get_triangle(angle);
        draw.fill_triangle(tri, '=');
        draw.draw_line(ccom::AbsoluteLine({15, 19}, tri.a), ' ');
        draw.draw_line(ccom::AbsoluteLine({15, 19}, tri.b), ' ');
        draw.draw_line(ccom::AbsoluteLine({15, 19}, tri.c), ' ');
        draw.draw_line(ccom::AbsoluteLine({30, 10}, tri.a), '@');
        draw.draw_line(ccom::AbsoluteLine({30, 10}, tri.b), '@');
        draw.draw_line(ccom::AbsoluteLine({30, 10}, tri.c), '@');

        draw.flush_buffer(std::cout);
        draw.clear_buffer(':');
        std::cout << "\x1b[A\x1b[2K" << "FPS: " << fps << ",\tElapsed time: " << elapsed_time << ",\tFrame time:" << frame_time << std::endl;
        angle += frame_time;
    });
}
