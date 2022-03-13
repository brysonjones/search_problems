
#include "robot.hpp"

// Member functions definitions including constructor
Robot::Robot() {}

int Robot::setup(std::vector<int> initial_state,
                 std::vector<int> map_size, 
                 std::vector<Obstacle> *obstacles) {
    state = initial_state;
    _obstacles = obstacles;
}

int Robot::initPlanner(std::vector<int> goal_pose, std::vector<int> map_bounds){
    planner.setup(state, goal_pose, map_bounds, _obstacles);
    planner.main();
}

int Robot::updatePlan(){
    planner.updatePosition(state);
    planner.main();

    return 0;
}

int Robot::updateGoal(std::vector<int> goal){
    planner.updateGoal(goal);
    planner.main();

    return 0;
}

const std::deque<std::vector<int>>* Robot::getPlan(){
    return planner.path;
}

// move() takes the first value of the current motion plan and steps
// in that direction
int Robot::move(){
    state = planner.path->at(0);
    planner.path->pop_front();

    return 0;
}
