#pragma once
#include <ccom/util.hpp>

#include <iostream>
#include <array>
#include <cmath>

namespace ccom::geometry {

template <typename T>
class Point {
public:
    Point()
        : x(T())
        , y(T()) { }
    Point(const T& x, const T& y)
        : x(x)
        , y(y) { }

    T x;
    T y;
};

template <typename T>
class Triangle {
public:
    Triangle() = delete;
    Triangle(const Point<T>& a, const Point<T>& b, const Point<T>& c)
        : a(a)
        , b(b)
        , c(c) { }
    Triangle(const std::array<Point<T>, 3>& coords)
        : a(coords[0])
        , b(coords[1])
        , c(coords[2]) { }

    std::array<Point<T>, 3> get_points() const {
        std::array<Point<T>, 3> arr;
        arr[0] = a;
        arr[1] = b;
        arr[2] = c;
        return arr;
    }

    Point<T> a;
    Point<T> b;
    Point<T> c;
};

template <typename T>
class Line {
public:
    Line() = delete;
    Line(const Point<T>& start, const Point<T>& end)
        : start(start)
        , end(end) { }
    Line(const std::array<Point<T>, 2>& coords)
        : start(coords[0])
        , end(coords[1]) { }

    std::array<Point<T>, 2> get_points() const {
        std::array<Point<T>, 2> arr;
        arr[0] = start;
        arr[1] = end;
        return arr;
    }

    Point<T> start;
    Point<T> end;
};

Point<int> relative_to_absolute_point(const Point<double>& pt, int width, int height); // Implemented in src/geometry.cpp

template <template <typename T> typename Container>
Container<int> relative_to_absolute(const Container<double>& container, int width, int height) {
    auto relative_coords = container.get_points();
    auto absolute_coords = map_array(
        relative_coords,
        [width, height](const Point<double>& pt) {
            return relative_to_absolute_point(pt, width, height);
        }
    );
    return Container<int>(absolute_coords);
}

using RelativePoint    = Point<double>;
using RelativeTriangle = Triangle<double>;
using RelativeLine     = Line<double>;

using AbsolutePoint    = Point<int>;
using AbsoluteTriangle = Triangle<int>;
using AbsoluteLine     = Line<int>;

} // namespace ccom::geometry
