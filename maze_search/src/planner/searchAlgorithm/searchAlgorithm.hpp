#pragma once

#include <vector>

#include "aStar/aStar.hpp"


class Planner {
    public:
        Planner();
        int setup();
        int search();
        int main();

    private:
        AStar aStarSearch{};
        std::vector<int> initialState;
        std::vector<int> goalState;

};
 