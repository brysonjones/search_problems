
#include "aStar.hpp"


AStar::AStar() {}

int AStar::setup(std::vector<int> robot_start_pose, std::vector<int> goal_pose) {
    
    // store start and goal poses
    initial_state = robot_start_pose;
    goal_state = goal_pose;

    // initialize the starting node of the robot
    Node start_node;
    start_node.parent = nullptr;
    start_node.node_pose = {initial_state[0], initial_state[1]};
    start_node.g = 0;
    start_node.h = 0;
    start_node.f = 0;

    // push the start node to the open list
    open_list.push(start_node);
}


bool AStar::isStateValid(Node state)
{ 
    // Returns true if x and y of s_prime is in range 
    return (state.node_pose[0] > 0) && 
            (state.node_pose[0] <= x_size) && 
            (state.node_pose[1] > 0) && 
            (state.node_pose[1] <= y_size); 
} 


int AStar::getHeuristic(Node state){

}

std::stack<std::vector<int>> AStar::computePath(){

    // while(sgoal is not expanded and OPEN ≠ 0)
    // remove s with the smallest [f(s) = g(s)+h(s)] from OPEN;
    // expand s;
}
 