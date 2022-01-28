
#include "aStar.hpp"


AStar::AStar() {}

int AStar::setup(std::vector<int> robot_start_pose, std::vector<int> goal_pose, 
                 std::vector<std::vector<int>> &enviro_map) {
    
    // store start and goal poses
    initial_state = robot_start_pose;
    goal_state = goal_pose;
    map = &enviro_map; // TOOD: verify this is storing the data properly
    x_size = map->size();
    y_size = map[0].size();

    // initialize the starting node of the robot
    Node start_node;
    start_node.parent = nullptr;
    start_node.node_pose = {initial_state[0], initial_state[1]};
    start_node.g = 0;
    start_node.h = 0;
    start_node.f = 0;

    // push the start node to the open list
    open_list.push(start_node);
    open_list_map[initial_state] = start_node;
}


bool AStar::isStateValid(Node state)
{ 
    // Returns true if x and y of s_prime is in range 
    return ((state.node_pose[0] >= 0) && 
            (state.node_pose[0] <= x_size) && 
            (state.node_pose[1] >= 0) && 
            (state.node_pose[1] <= y_size)); 
} 

bool AStar::isGoalExpanded(){

    if (closed_list.find(goal_state) == closed_list.end())
    {
        return false;
    }
}


int AStar::getH(Node state){
    // use euclidean distance for now
    int dx_to_goal = abs(state.node_pose[0] - goal_state[0]);
    int dy_to_goal = abs(state.node_pose[1] - goal_state[1]);
            
    int h_val = sqrt((dx_to_goal * dx_to_goal) + (dy_to_goal * dy_to_goal));

    return h_val;
}

int AStar::getG(std::vector<int> &state){
    if (open_list_map.find(state) != open_list_map.end()){
        return open_list_map[state].g;
    }
    return MAX_COST;
}

Node AStar::popOpenList(){
    Node state = open_list.top();
    closed_list[state.node_pose] = state;
    open_list.pop();

    return state;
}

void AStar::insertIntoOpenList(Node &current_state, Node &state_prime){
    Node state = state_prime;
    state.g = current_state.g + cost;
    state.h = getH(state);
    state.f = state.g + state.h;
    open_list.push(state);
    open_list_map[state.node_pose] = state;

}

void AStar::computePath(){
    Node current_state;
    Node state_prime;

    // while(sgoal is not expanded and OPEN ≠ 0) -- done in setup fcn
    while(!isGoalExpanded() && !open_list.empty()){
        // remove s with the smallest [f(s) = g(s)+h(s)] from OPEN;
        // insert s into CLOSED;
        current_state = popOpenList();

        // std::cout << "Current State - X: " << current_state.node_pose[0] 
        //         << ", Y: " << current_state.node_pose[1] << std::endl;

        // for every successor s’ of s such that s’ not in CLOSED
        for (int i = 0; i < NUMOFDIRS; i++){
            // update s' location
            // std::cout << state_prime.node_pose[0] << "\n";
            state_prime.node_pose[0] = current_state.node_pose[0] + dX[i];
            state_prime.node_pose[1] = current_state.node_pose[1] + dY[i]; 
            state_prime.parent = &closed_list[current_state.node_pose];
            if (!isStateValid(state_prime)){continue;}
            // if g(s’) > g(s) + c(s,s’)
            if (closed_list.find(state_prime.node_pose) == closed_list.end() &&
                getG(state_prime.node_pose) > current_state.g + cost){
                // g(s’) = g(s) + c(s,s’);
                // insert s’ into OPEN;
                insertIntoOpenList(current_state, state_prime); 
            }
        }
    }
    return;
}

void AStar::backTracePath(){
        path.push_front(closed_list[goal_state].node_pose);
        std::cout << "Pose - X: " << closed_list[goal_state].node_pose[0] 
                  << ", Y: " << closed_list[goal_state].node_pose[1] << std::endl;

        // init Node obj to iterate with
        Node* mostRecentNode;
        
        mostRecentNode = closed_list[goal_state].parent;
        
        // push node to the top of the stack
        path.push_front(mostRecentNode->node_pose);
        std::cout << "Pose - X: " << mostRecentNode->node_pose[0] 
                << ", Y: " << mostRecentNode->node_pose[1] << std::endl;
        
        while (mostRecentNode->parent != nullptr){
            // assign the parent of the mostRecentNode to become the Node
            mostRecentNode = mostRecentNode->parent;
            path.push_front(mostRecentNode->node_pose);
            std::cout << "Pose - X: " << mostRecentNode->node_pose[0] 
                    << ", Y: " << mostRecentNode->node_pose[1] << std::endl;
        }
    }
 