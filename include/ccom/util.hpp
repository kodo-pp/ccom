#pragma once
#include <type_traits>

template <typename Integer>
Integer rounded_integer_division(const Integer& a, const Integer& b) {
    static_assert(std::is_integral_v<Integer>, "Arguments should be integer for rounded_integer_division()");
    return ((2 * a / b) + 1) / 2;
}
