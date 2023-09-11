#include "vec3.hpp"
#include "ray.hpp"

#pragma once

struct Sphere {
    const Point3 center;
    const double radius;

    bool hit(const Ray& r) {
        Vec3 oc = r.origin() - center;
        auto a = dot(r.direction(), r.direction());
        auto b = 2.0 * dot(oc, r.direction());
        auto c = dot(oc, oc) - radius*radius;
        auto discriminant = b*b - 4*a*c;
        return (discriminant >= 0);
    }
};
