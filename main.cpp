#include <array>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <numbers>
#include <random>

#include "geometry.hpp"
#include "object.hpp"
#include "ray.hpp"

static auto ToCamera(const Vec2f& pixel, uint16_t width, uint16_t height, float fov) {
    using namespace std::numbers;

    auto ndc            = Vec2f(pixel.x / width, pixel.y / height);
    auto aspect_ratio   = width / (float)height;
    auto fov_multiplier = std::tan(fov / 2 * pi / 180);
    auto screen         = Vec2f(
        (2 * ndc.x - 1) * aspect_ratio * fov_multiplier, (1 - 2 * ndc.y) * fov_multiplier);

    return Vec3f(screen.x, screen.y, -1);
}

int main() {

    constexpr auto WIDTH  = 640;
    constexpr auto HEIGHT = 480;
    constexpr auto FOV    = 51.52f;

    auto dev = std::random_device();
    auto gen = std::mt19937(dev());
    auto dis = std::uniform_real_distribution<>(0, 1);

    const auto cameraToWorld = Matrix44f(
        0.945519,
        0,
        -0.325569,
        0,
        -0.179534,
        0.834209,
        -0.521403,
        0,
        0.271593,
        0.551447,
        0.78876,
        0,
        4.208271,
        8.374532,
        17.932925,
        1);

    auto frame_buffer = std::array<uint8_t, WIDTH * HEIGHT * 3>{0};

    auto origin_world = Vec3f();
    cameraToWorld.multVecMatrix(Vec3f(), origin_world);

    auto objects = std::array<std::unique_ptr<Object>, 32>();

    gen.seed(0);

    // Generate random spheres
    for (auto i = 0; i < objects.size(); i++) {
        auto randPos = Vec3f((0.5 - dis(gen)) * 10, (0.5 - dis(gen)) * 10, (0.5 + dis(gen) * 10));
        auto randRadius = float(0.5 + dis(gen) * 0.5);
        auto randColor  = Vec3f{(float)dis(gen), (float)dis(gen), (float)dis(gen)};

        objects[i] = std::make_unique<Sphere>(randPos, randRadius, randColor);
    }

    for (auto i = 0; i < HEIGHT; i++) {
        for (auto j = 0; j < WIDTH; j++) {

            auto point_world = Vec3f();

            cameraToWorld.multVecMatrix(
                ToCamera(Vec2f(j + .5f, i + .5f), WIDTH, HEIGHT, FOV), point_world);

            auto direction_world = point_world - origin_world;
            direction_world.normalize();

            auto ray = Ray(origin_world, direction_world);

            // std::cout << "i: " << i << std::endl;
            // std::cout << "j: " << j << std::endl << std::endl;
            for (const auto& object : objects) {
                if (object->intersects(ray)) {
                    auto index            = i * WIDTH + j;
                    frame_buffer[index]   = 255;
                    frame_buffer[++index] = 255;
                    frame_buffer[++index] = 255;
                }
            }
        }
    }

    auto ofs = std::ofstream("./out.ppm");
    ofs << "P5\n" << WIDTH << " " << HEIGHT << "\n255\n";
    ofs.write((char*)frame_buffer.data(), WIDTH * HEIGHT * 3);

    return 0;
}