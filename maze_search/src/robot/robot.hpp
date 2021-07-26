#pragma once
#include <vector>


class Robot {
    public:
        Robot();
        int setup();

    private:
        std::vector<int> state; // 1D, 2 values for (X, Y)

};
 