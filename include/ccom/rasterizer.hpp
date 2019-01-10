#pragma once
#include <ccom/geometry.hpp>

#include <utility>
#include <vector>
#include <string>
#include <shared_mutex>
#include <iosfwd>

namespace ccom {

class Rasterizer {
public:
    Rasterizer() = default;
    Rasterizer(const Rasterizer& other) = delete;
    Rasterizer& operator=(const Rasterizer& other) = delete;

    void set_buffer_size(int width, int height, char clear_char = ' ');

    void draw_point(
        const geometry::AbsolutePoint& pt,
        char fill_char
    );
    void draw_point(
        std::vector<std::string>& buffer,
        const geometry::AbsolutePoint& pt,
        char fill_char
    );

    void draw_line(
        const geometry::AbsoluteLine& line,
        char fill_char
    );
    void draw_line(
        std::vector<std::string>& buffer,
        const geometry::AbsoluteLine& line,
        char fill_char
    );

    void fill_triangle(
        const geometry::AbsoluteTriangle& tri,
        char fill_char
    );
    void fill_triangle(
        std::vector<std::string>& buffer,
        const geometry::AbsoluteTriangle& tri,
        char fill_char
    );

    void flush_buffer(std::ostream& out) const;
    void clear_buffer(char clear_char = ' ');
    
private:
    mutable std::shared_mutex mutex;
    mutable bool complete_redraw_flag = true;
    std::vector<std::string> buffer;
};

Rasterizer& get_rasterizer();

} // namespace ccom
