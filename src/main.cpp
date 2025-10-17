#include <print>

#include "Random.h"
#include "Vec2.hpp"

int main() {
    std::print("Hello, ShootEm!\n");

    srand(time(nullptr));
    Vec2f pos{ Random::between(0.0f, 100.0f), Random::between(0.0f, 100.0f) };
    std::print("Random Position: ({}, {})\n", pos.x, pos.y);
    return 0;
}
