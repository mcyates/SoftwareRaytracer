#include <thread>
#include <iostream>
#include <vector>

#include "src/rtweekend.h"

#include "src/camera.h"
#include "src/color.h"
#include "src/hittableList.h"
#include "src/material.h"
#include "src/sphere.h"

using namespace std;

color rayColor(const ray &r, const hittable &world, int depth)
{
    hitRecord rec;
    // if  we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
    {
        return color(0, 0, 0);
    }

    if (world.hit(r, 0.001, infinity, rec))
    {
        ray scattered;
        color attenuation;
        if (rec.matPtr->scatter(r, rec, attenuation, scattered))
            return attenuation * rayColor(scattered, world, depth - 1);
        return color(0, 0, 0);
    }

    vec3 unitDirection = unit_vector(r.direction());
    auto t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const auto aspectRatio = 16.0 / 9.0;
    const int imageWidth = 900;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 50;
    const int maxDepth = 50;

    // World
    hittableList world;
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8));
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2));

    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

    // Camera
    camera cam;

    // Render

    cout << "P3\n"
         << imageWidth << ' ' << imageHeight << "\n255\n";

    // for (int j = imageHeight; j >= 0; j--)
    // {
    //     cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

    //     for (int i = 0; i < imageWidth; i++)
    //     {
    //         color pixelColor(0, 0, 0);
    //         for (int s = 0; s < samplesPerPixel; ++s)
    //         {
    //             auto u = double(i + random_double()) / (imageWidth - 1);
    //             auto v = double(j + random_double()) / (imageHeight - 1);
    //             ray r = cam.getRay(u, v);
    //             pixelColor += rayColor(r, world, maxDepth);
    //         }

    //         WriteColor(cout, pixelColor, samplesPerPixel);
    //     }
    // }
    // std::cerr << "\nDone.\n";
    return 0;
}