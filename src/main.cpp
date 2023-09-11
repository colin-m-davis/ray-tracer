#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"
#include <iostream>
#include <algorithm>

Color ray_color(const Ray& r) {
    const Vec3 unit_direction = unit_vector(r.direction());
    const auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
}

int main() {
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    const int image_height = std::max(1, static_cast<int>(image_width / aspect_ratio));

    // Camera
    const auto focal_length = 1.0;
    const auto viewport_height = 2.0;
    const auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
    const auto camera_center = Point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    const auto viewport_u = Vec3(viewport_width, 0, 0);
    const auto viewport_v = Vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    const auto pixel_delta_u = viewport_u / image_width;
    const auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    const auto viewport_upper_left = camera_center - Vec3(0, 0, focal_length)
                                     - viewport_u/2 - viewport_v/2;
    const auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            const auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            const auto ray_direction = pixel_center - camera_center;
            const Ray r(camera_center, ray_direction);

            const Color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.\n";
}
