#pragma once
#include <cmath>
#include <random>

struct vec3 {
    double x = 0;
    double y = 0;
    double z = 0;

    vec3() = default;
    vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    double length_sq() const {
        return x*x + y*y + z*z;
    }

    double length() const {
        return std::sqrt(length_sq());
    }

    

};