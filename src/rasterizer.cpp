#include <ccom/rasterizer.hpp>
#include <ccom/util.hpp>
#include <ccom/geometry.hpp>

#include <sstream>
#include <algorithm>
#include <shared_mutex>

namespace ccom
{

void Rasterizer::draw_line(
    const geometry::AbsoluteLine& line,
    char fill_char
) {
    draw_line(buffer, line, fill_char);
}

void Rasterizer::draw_line(
    std::vector<std::string>& buffer,
    const geometry::AbsoluteLine& line,
    char fill_char
) {
    auto start = line.start;
    auto end = line.end;
    auto delta_x = end.x - start.x;
    auto delta_y = end.y - start.y;

    if (delta_y == 0) {
        for (auto i = std::min(start.x, end.x); i <= std::max(start.x, end.x); ++i) {
            buffer.at(start.y).at(i) = fill_char;
        }
        return;
    } else if (delta_x == 0) {
        for (auto i = std::min(start.y, end.y); i <= std::max(start.y, end.y); ++i) {
            buffer.at(i).at(start.x) = fill_char;
        }
        return;
    }

    auto from = start;
    auto to = end;

    if (abs(delta_x) > abs(delta_y)) {
        if (to.x < from.x) {
            std::swap(from, to);
            delta_x = -delta_x;
            delta_y = -delta_y;
        }

        auto base_x = from.x;
        auto base_y = from.y;
        for (int i = 0; i <= delta_x; ++i) {
            auto point_x = base_x + i;
            auto point_y = base_y + rounded_integer_division(i * delta_y, delta_x);
            buffer.at(point_y).at(point_x) = fill_char;
        }
    } else {
        if (to.y < from.y) {
            std::swap(from, to);
            delta_x = -delta_x;
            delta_y = -delta_y;
        }

        auto base_x = from.x;
        auto base_y = from.y;
        for (int i = 0; i <= delta_y; ++i) {
            auto point_x = base_x + rounded_integer_division(i * delta_x, delta_y);
            auto point_y = base_y + i;
            buffer.at(point_y).at(point_x) = fill_char;
        }
    }
}

void Rasterizer::fill_triangle(
    const geometry::AbsoluteTriangle& tri,
    char fill_char
) {
    fill_triangle(buffer, tri, fill_char);
}

void Rasterizer::fill_triangle(
    std::vector<std::string>& buffer,
    const geometry::AbsoluteTriangle& tri,
    char fill_char
) {
    auto v1 = tri.a;
    auto v2 = tri.b;
    auto v3 = tri.c;

    auto min_x = std::min(std::min(v1.x,  v2.x),  v3.x);
    auto min_y = std::min(std::min(v1.y, v2.y), v3.y);
    auto max_x = std::max(std::max(v1.x,  v2.x),  v3.x);
    auto max_y = std::max(std::max(v1.y, v2.y), v3.y);

    int delta_x = max_x - min_x + 1;
    int delta_y = max_y - min_y + 1;
    std::vector<std::string> temporary_buffer(delta_y, std::string(delta_x, '?'));

    auto x1 = v1.x - min_x;
    auto x2 = v2.x - min_x;
    auto x3 = v3.x - min_x;
    auto y1 = v1.y - min_y;
    auto y2 = v2.y - min_y;
    auto y3 = v3.y - min_y;

    draw_line(temporary_buffer, {{x1, y1}, {x2, y2}}, '1');
    draw_line(temporary_buffer, {{x1, y1}, {x3, y3}}, '1');
    draw_line(temporary_buffer, {{x2, y2}, {x3, y3}}, '1');
    
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

void Rasterizer::flush_buffer(std::ostream& out) const {
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

void Rasterizer::clear_buffer(char clear_char) {
    for (auto& line : buffer) {
        for (auto& ch : line) {
            ch = clear_char;
        }
    }
}

void Rasterizer::set_buffer_size(int width, int height, char clear_char) {
    buffer.resize(height);
    for (auto& line : buffer) {
        line.resize(width, clear_char);
    }
    complete_redraw_flag = true;
}

Rasterizer& get_rasterizer() {
    static Rasterizer rasterizer;
    return rasterizer;
}

} // namespace ccom
