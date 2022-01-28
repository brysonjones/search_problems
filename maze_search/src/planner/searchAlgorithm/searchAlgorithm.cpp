
#include "searchAlgorithm.hpp"

// Member functions definitions including constructor
Planner::Planner(void) {
}

int Planner::setup(std::vector<int> robot_pose, std::vector<int> goal_pose, 
                   std::vector<std::vector<int>> &enviro_map) {
    aStarSearch.setup(robot_pose, goal_pose, enviro_map);
    
    return 0;

}

int Planner::main() {
    
    aStarSearch.computePath();
    aStarSearch.backTracePath();

    return 0;
}