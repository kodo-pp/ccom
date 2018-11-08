#pragma once
#include <shared_mutex>
#include <functional>

namespace ccom {

struct StopDrawLoop {};

class DrawLoopManager {
public:
    DrawLoopManager() = default;
    DrawLoopManager(const DrawLoopManager& other) = delete;
    DrawLoopManager& operator=(const DrawLoopManager& other) = delete;

    void set_max_fps(int fps);
    int get_max_fps() const;

    void run_draw_loop(const std::function<void(double, double, double)>& func) const;

private:
    mutable std::shared_mutex mutex;
    int max_fps = 30;
};

DrawLoopManager& get_draw_loop_manager();

} // namespace ccom
