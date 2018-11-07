#include <ccom/draw_manager.hpp>
#include <ccom/util.hpp>
#include <sstream>

#include <algorithm>

namespace ccom
{

void DrawManager::draw_line(
    const std::pair<int, int>& start,
    const std::pair<int, int>& end,
    char fill_char
) {
    draw_line(buffer, start, end, fill_char);
}

void DrawManager::draw_line(
    std::vector<std::string>& buffer,
    const std::pair<int, int>& start,
    const std::pair<int, int>& end,
    char fill_char
) {
    auto delta_x = end.first - start.first;
    auto delta_y = end.second - start.second;

    if (delta_y == 0) {
        for (auto i = std::min(start.first, end.first); i <= std::max(start.first, end.first); ++i) {
            buffer.at(start.second).at(i) = fill_char;
        }
        return;
    } else if (delta_x == 0) {
        for (auto i = std::min(start.second, end.second); i <= std::max(start.second, end.second); ++i) {
            buffer.at(i).at(start.first) = fill_char;
        }
        return;
    }

    auto from = start;
    auto to = end;

    if (abs(delta_x) > abs(delta_y)) {
        if (to.first < from.first) {
            std::swap(from, to);
            delta_x = -delta_x;
            delta_y = -delta_y;
        }

        auto base_x = from.first;
        auto base_y = from.second;
        for (int i = 0; i <= delta_x; ++i) {
            auto point_x = base_x + i;
            auto point_y = base_y + rounded_integer_division(i * delta_y, delta_x);
            buffer.at(point_y).at(point_x) = fill_char;
        }
    } else {
        if (to.second < from.second) {
            std::swap(from, to);
            delta_x = -delta_x;
            delta_y = -delta_y;
        }

        auto base_x = from.first;
        auto base_y = from.second;
        for (int i = 0; i <= delta_y; ++i) {
            auto point_x = base_x + rounded_integer_division(i * delta_x, delta_y);
            auto point_y = base_y + i;
            buffer.at(point_y).at(point_x) = fill_char;
        }
    }
}

void DrawManager::fill_triangle(
    const std::pair<int, int>& v1,
    const std::pair<int, int>& v2,
    const std::pair<int, int>& v3,
    char fill_char
) {
    fill_triangle(buffer, v1, v2, v3, fill_char);
}

void DrawManager::fill_triangle(
    std::vector<std::string>& buffer,
    const std::pair<int, int>& v1,
    const std::pair<int, int>& v2,
    const std::pair<int, int>& v3,
    char fill_char
) {
    auto min_x = std::min(std::min(v1.first,  v2.first),  v3.first);
    auto min_y = std::min(std::min(v1.second, v2.second), v3.second);
    auto max_x = std::max(std::max(v1.first,  v2.first),  v3.first);
    auto max_y = std::max(std::max(v1.second, v2.second), v3.second);

    int delta_x = max_x - min_x + 1;
    int delta_y = max_y - min_y + 1;
    std::vector<std::string> temporary_buffer(delta_y, std::string(delta_x, '?'));

    auto x1 = v1.first - min_x;
    auto x2 = v2.first - min_x;
    auto x3 = v3.first - min_x;
    auto y1 = v1.second - min_y;
    auto y2 = v2.second - min_y;
    auto y3 = v3.second - min_y;

    draw_line(temporary_buffer, {x1, y1}, {x2, y2}, '1');
    draw_line(temporary_buffer, {x1, y1}, {x3, y3}, '1');
    draw_line(temporary_buffer, {x2, y2}, {x3, y3}, '1');
    
    for (auto& line : temporary_buffer) {
        for (int j = 0; j < static_cast<int>(line.length()) && line.at(j) != '1'; ++j) {
            line.at(j) = '0';
        }
        for (int j = line.length() - 1; j >= 0 && line.at(j) != '1'; --j) {
            line.at(j) = '0';
        }
    }
    
    for (int i = 0; i < delta_y; ++i) {
        for (int j = 0; j < delta_x; ++j) {
            if (temporary_buffer.at(i).at(j) != '0') {
                buffer.at(i + min_y).at(j + min_x) = fill_char;
            }
        }
    }
}

void DrawManager::flush_buffer(std::ostream& out) const {
    std::stringstream text_buffer;
    if (complete_redraw_flag) {
        complete_redraw_flag = false;
        text_buffer << "\x1b[3J\x1b[H\x1b[J"; // Clear screen
    }
    text_buffer << "\x1b[0;0H"; // Put cursor to (0, 0)

    for (const auto& line : buffer) {
        text_buffer << line << '\n';
    }
    out << text_buffer.str();
    out.flush();
}

void DrawManager::clear_buffer(char clear_char) {
    for (auto& line : buffer) {
        for (auto& ch : line) {
            ch = clear_char;
        }
    }
}

void DrawManager::set_buffer_size(int width, int height, char clear_char) {
    buffer.resize(height);
    for (auto& line : buffer) {
        line.resize(width, clear_char);
    }
    complete_redraw_flag = true;
}

DrawManager& get_draw_manager() {
    static DrawManager draw_manager;
    return draw_manager;
}

} // namespace ccom
