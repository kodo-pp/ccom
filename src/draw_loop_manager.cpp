#include <ccom/draw_loop_manager.hpp>

#include <chrono>
#include <unistd.h>

namespace ccom {

void DrawLoopManager::set_max_fps(int fps) {
    std::unique_lock<std::shared_mutex> lock(mutex);
    max_fps = fps;
}

int DrawLoopManager::get_max_fps() const {
    std::shared_lock<std::shared_mutex> lock(mutex);
    return max_fps;
}

void DrawLoopManager::run_draw_loop(const std::function<void(double, double, double)>& func) const {
    auto start_time = std::chrono::high_resolution_clock::now();
    auto last_render_time = std::chrono::high_resolution_clock::now();
    int frames = 0;
    while (true) {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> seconds_after_last_render = now - last_render_time;
        auto time_after_last_render = seconds_after_last_render.count();
        std::chrono::duration<double> seconds_elapsed = now - start_time;
        auto elapsed_time = seconds_elapsed.count();

        std::shared_lock <std::shared_mutex> lock(mutex);
        const auto min_time_after_last_render = 1.0 / max_fps;
        lock.unlock();

        try {
            func(frames / elapsed_time, elapsed_time, time_after_last_render);
        } catch (const StopDrawLoop&) {
            break;
        }
        last_render_time = now;
        ++frames;
        if (time_after_last_render < min_time_after_last_render) {
            auto diff = min_time_after_last_render - time_after_last_render;
            auto useconds_sleep = static_cast<int>(2e+6 * diff);
            usleep(useconds_sleep);
        }
    }
}

DrawLoopManager& get_draw_loop_manager() {
    static DrawLoopManager draw_loop_manager;
    return draw_loop_manager;
}

} // namespace ccom
