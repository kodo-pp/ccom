#pragma once
#include <type_traits>
#include <array>

template <typename Integer>
Integer rounded_integer_division(const Integer& a, const Integer& b) {
    static_assert(std::is_integral_v<Integer>, "Arguments must be integers");
    return ((2 * a / b) + 1) / 2;
}

template <typename Source, typename Func, size_t n>
auto map_array(const std::array<Source, n>& src, const Func& func) {
    using Dest = decltype(func(src[0]));
    static_assert(std::is_default_constructible_v<Dest>, "Destination type must be default-constructible");
    std::array<Dest, n> dest {{}};
    for (size_t i = 0; i < n; ++i) {
        dest[i] = func(src[i]);
    }
    return dest;
}
