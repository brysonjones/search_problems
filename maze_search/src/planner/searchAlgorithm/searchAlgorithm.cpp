
#include "searchAlgorithm.hpp"

// Member functions definitions including constructor
Planner::Planner(void) {
}

int Planner::setup(std::vector<int> robot_pose, std::vector<int> goal_pose, 
                   std::vector<int> map_bounds, std::vector<Obstacle> *obstacles) {             
    aStarSearch.setup(robot_pose, goal_pose, map_bounds, obstacles);
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
    aStarSearch.current_state[2] = robot_pose[2];

    aStarSearch.resetSearch(); // TODO: probably move this to another place?
}

int Planner::updateGoal(std::vector<int> goal_state){
    aStarSearch.goal_state[0] = goal_state[0];
    aStarSearch.goal_state[1] = goal_state[1];
    aStarSearch.goal_state[2] = goal_state[2];

    aStarSearch.resetSearch(); // TODO: probably move this to another place?
}