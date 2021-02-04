#include "geometry.hpp"

int main() {
    constexpr auto WIDTH  = 500;
    constexpr auto HEIGHT = 500;

    for (auto i = 0; i < HEIGHT; i++) {
        for (auto j = 0; j < WIDTH; j++) {
            auto pixel = Vec2f(i + .5f, j + .5f);
        }
    }
    return 0;
}