#ifndef Q1_H
#define Q1_H

#include <functional>
#include <cstdlib>


namespace q1 {
inline double gradient_descent(double initial_value, double step_size, std::function<double(double)> func) {
    const double delta = 0.01;
    const double threshold = 1e-9;
    while (true) {
        double grad = (func(initial_value + delta) - func(initial_value - delta)) / delta / 2;
        double dx = -grad * step_size;
        initial_value += dx;
        if (std::abs(dx) < threshold) break;
    }
    return initial_value;
}

template <typename ValType, typename Functor>
inline double gradient_descent(ValType initial_value, double step_size) {
    Functor func;
    const double delta = 0.01;
    const double threshold = 1e-9;
    while (true) {
        double grad = (func(initial_value + delta) - func(initial_value - delta)) / delta / 2;
        double dx = -grad * step_size;
        initial_value += dx;
        if (std::abs(dx) < threshold) break;
    }
    return initial_value;
}

};  // namespace q1
#endif  // Q1_H