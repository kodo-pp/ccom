#pragma once
#include <utility>
#include <vector>
#include <string>
#include <shared_mutex>
#include <iosfwd>

namespace ccom {

class DrawManager {
public:
    DrawManager() = default;
    DrawManager(const DrawManager& other) = delete;
    DrawManager& operator=(const DrawManager& other) = delete;

    void set_buffer_size(int width, int height, char clear_char = ' ');

    void draw_line(const std::pair<int, int>& start, const std::pair<int, int>& end, char fill_char);
    void draw_line(
        std::vector<std::string>& buffer,
        const std::pair<int, int>& start,
        const std::pair<int, int>& end,
        char fill_char
    );
    void fill_triangle(
        const std::pair<int, int>& v1,
        const std::pair<int, int>& v2,
        const std::pair<int, int>& v3,
        char fill_char
    );
    void fill_triangle(
        std::vector<std::string>& buffer,
        const std::pair<int, int>& v1,
        const std::pair<int, int>& v2,
        const std::pair<int, int>& v3,
        char fill_char
    );

    void flush_buffer(std::ostream& out) const;
    void clear_buffer(char clear_char = ' ');
    
private:
    mutable std::shared_mutex mutex;
    mutable bool complete_redraw_flag = true;
    std::vector <std::string> buffer;
};

DrawManager& get_draw_manager();

} // namespace ccom
