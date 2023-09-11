#pragma once

#include "vec3.hpp"

class Ray {
public:
    Ray() = default;
    Ray(const Point3& origin, const Vec3& direction) : orig(origin), dir(direction) {}

private:
    Point3 orig;
    Vec3 dir;
};
