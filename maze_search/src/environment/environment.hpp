#pragma once
#include <vector>

struct Obstacle {
    std::vector<int> state = {0, 0};  // <x, y> position on map
    std::vector<int> dims = {50, 300};  // <width, height> diemnsions of obstacle
};
