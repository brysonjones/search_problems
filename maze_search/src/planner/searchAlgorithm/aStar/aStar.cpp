
#include "aStar.hpp"


AStar::AStar() {}

int AStar::setup(std::vector<int> robot_start_pose, std::vector<int> goal_pose, 
                 std::vector<std::vector<int>> &enviro_map) {
    
    // store start and goal poses
    initial_state = robot_start_pose;
    goal_state = goal_pose;
    map = &enviro_map; // TOOD: verify this is storing the data properly

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

bool AStar::isGoalExpanded(){

    if (closed_list.find(goal_state) == closed_list.end())
    {
        return false;
    }
}


int AStar::getHeuristic(Node state){
    // use euclidean distance for now
    int dx_to_goal = abs(state.node_pose[0] - goal_state[0]);
    int dy_to_goal = abs(state.node_pose[1] - goal_state[1]);
            
    int h_val = sqrt((dx_to_goal * dx_to_goal) + (dy_to_goal * dy_to_goal));

    return h_val;
}

std::stack<std::vector<int>> AStar::computePath(){

    // while(sgoal is not expanded and OPEN ≠ 0) -- done in setup fcn
    while(!isGoalExpanded() && !open_list.empty()){
    // remove s with the smallest [f(s) = g(s)+h(s)] from OPEN;
    // insert s into CLOSED;
    // for every successor s’ of s such that s’ not in CLOSED
        // if g(s’) > g(s) + c(s,s’)
            // g(s’) = g(s) + c(s,s’);
            // insert s’ into OPEN;
    }
}
 