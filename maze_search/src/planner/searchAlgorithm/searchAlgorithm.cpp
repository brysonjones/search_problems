
#include "searchAlgorithm.hpp"

// Member functions definitions including constructor
Planner::Planner(void) {
}

int Planner::setup(std::vector<int> robot_pose, std::vector<int> goal_pose, std::vector<int> map_bounds) {
                       
    aStarSearch.setup(robot_pose, goal_pose, map_bounds);
    
    return 0;

}

int Planner::main() {
    
    aStarSearch.computePath();
    aStarSearch.backTracePath();

    path = &aStarSearch.path;

    return 0;
}

int Planner::updatePosition(std::vector<int> robot_pose){
    aStarSearch.current_state[0] = robot_pose[0];
    aStarSearch.current_state[1] = robot_pose[1];

    aStarSearch.resetSearch(); // TODO: probably move this to another place?
}