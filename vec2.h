#ifndef VAC2_HPP
#define VAC2_HPP
#include <cmath>

struct Vec2 {
    float x, y;

    Vec2(float x = 0, float y = 0) : x(x), y(y) {}

    Vec2 operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }
    Vec2 operator-(const Vec2& other) const { return Vec2(x - other.x, y - other.y); }
    Vec2& operator+=(const Vec2& other) { // <-- Corretto!
        x += other.x;
        y += other.y;
        return *this;
    }
    Vec2& operator-=(const Vec2& other) { // <-- Corretto!
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vec2 operator*(float scalar) const { return Vec2(x * scalar, y * scalar); }
    Vec2 operator/(float scalar) const { return Vec2(x / scalar, y / scalar); }

    Vec2 operator-() const { return Vec2(-x, -y); }

    float dot(const Vec2& other) const { return x * other.x + y * other.y; }
    float length() const { return std::sqrt(x*x + y*y); }
    Vec2 normalized() const {
        float len = length();
        return len > 0 ? (*this)*(1.0f/len) : *this;
    }
};
#endif //VAC2_HPP