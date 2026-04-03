#pragma once
#include <cmath>
#include <random>

struct vec3 {
    double x = 0;
    double y = 0;
    double z = 0;

    vec3() = default;
    vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    /* component wise operations through operator overloads */
    vec3 operator+(const vec3& rhs) const {
        return {x+rhs.x, y+rhs.y, z+rhs.z};
    }

    vec3 operator-(const vec3& rhs) const {
        return {x-rhs.x, y-rhs.y, z-rhs.z};
    }

    vec3 operator-() const {
        return {-x, -y, -z};
    }

    vec3 operator*(double t) const {
        return {x*t, y*t, z*t};
    }

    vec3 operator*(const vec3& rhs){
        return {x*rhs.x, y*rhs.y, z*rhs.z};
    }

    vec3 operator/(double t) const {
        return *this * (1.0/t);
    }

    vec3& operator+=(const vec3& rhs){
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;

        return *this;
    } 
    
    double length_sq() const {
        return x*x + y*y + z*z;
    }

    double length() const {
        return std::sqrt(length_sq());
    }

    /* catch vectors that perfectly cancel surface normal */
    bool near_zero() const {
        const double e = 1e-8;
        return std::abs(x) < e && std::abs(y) < e && std::abs(z) < e;
    }

    /* standard vecmath helpers */
    inline vec3 norm(const vec3& v){
        return v / v.length();
    }

    inline double dot(const vec3& a, const vec3& b){
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }

    inline vec3 cross(const vec3& a, const vec3& b){
        return{
            a.y*b.z - a.z*b.y,
            a.z*b.x - a.x*b.z,
            a.x*b.y - a.y*b.x
        };
    }

    /* geometric vecmatch helpers */
    inline vec3 reflect(const vec3& incoming, const vec3& n){
        return incoming - n * (2.0 * dot(incoming, n));
    }

    inline vec3 refract(const vec3& incoming, const vec3& n, double etai_over_etat){
        double cos_theta = std::min(dot(-incoming, n), 1.0);
        vec3 r_out_perp = (incoming + n * cos_theta) * etai_over_etat;
        vec3 r_out_para = n * (-std::sqrt(std::abs(1.0 - r_out_perp.length_sq())));
        return r_out_perp + r_out_para;
    }

    /* misc helper functions */
    using point3 = vec3;
    using color = vec3;

    /* ensure each thread has its own rng to prevent corruption */
    inline double rand01(){
        thread_local static std::mt19937_64 rng{std::random_device{}()};
        thread_local static std::uniform_real_distribution<double> dist(0.0, 1.0);
        return dist(rng);
    }

    inline double rand_range(double lo, double hi){
        return lo + (hi - lo) * rand01();
    }

    inline vec3 random_in_unit_sphere(){
        while (true){
            vec3 p = {rand_range(-1,1), rand_range(-1,1), rand_range(-1,1)};
            if (p.length_sq() < 1.0) return p;
        }
    }

    inline vec3 random_unit_vector(){
        return norm(random_in_unit_sphere());
    }

    inline vec3 random_in_hemisphere(const vec3& normal){
        vec3 v = random_unit_vector();
        return dot(v, normal) > 0.0 ? v : -v;
    }

    inline vec3 random_in_unit_disk(){
        while (true){
            vec3 p = {rand_range(-1,1), rand_range(-1,1), 0};
            if (p.length_sq() < 1.0) return p;
        }
    }




};