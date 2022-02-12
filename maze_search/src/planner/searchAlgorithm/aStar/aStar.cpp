
#include "aStar.hpp"


AStar::AStar() {}

int AStar::setup(std::vector<int> robot_pose, std::vector<int> goal_pose, std::vector<int> map_bounds) {
    
    // store start and goal poses
    current_state = robot_pose;
    goal_state = goal_pose;

    // store map info
    x_bounds.push_back(map_bounds[0]);
    x_bounds.push_back(map_bounds[1]);
    y_bounds.push_back(map_bounds[2]);
    y_bounds.push_back(map_bounds[3]);

    // initialize the starting node of the robot
    Node start_node;
    start_node.parent = nullptr;
    start_node.node_pose = {current_state[0], current_state[1]};
    start_node.g = 0;
    start_node.h = 0;
    start_node.f = 0;

    // push the start node to the open list
    open_list.push(start_node);
    open_list_map[current_state] = start_node;
}

int AStar::resetSearch() {
    // ensure all lists are clear
    open_list = std::priority_queue<Node, std::vector<Node>, LessThanByF>();
    open_list_map.clear();
    closed_list.clear();
    path.clear();

    // initialize the starting node of the robot
    Node start_node;
    start_node.parent = nullptr;
    start_node.node_pose = {current_state[0], current_state[1]};
    start_node.g = 0;
    start_node.h = 0;
    start_node.f = 0;

    // push the start node to the open list
    open_list.push(start_node);
    open_list_map[current_state] = start_node;
}

bool AStar::isStateValid(Node state)
{ 
    // Returns true if x and y of s_prime is in range 
    return ((state.node_pose[0] >= x_bounds[0]) && 
            (state.node_pose[0] <= x_bounds[1]) && 
            (state.node_pose[1] >= y_bounds[0]) && 
            (state.node_pose[1] <= y_bounds[1])); 
} 

bool AStar::isGoalExpanded(){

    if (closed_list.find(goal_state) == closed_list.end())
    {
        return false;
    }

    return true;
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
    open_list_map.erase(state.node_pose);

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
    Node current_state_node;
    Node state_prime;

    // std::cout << "Open List Size: " << open_list.size() << std::endl;
    // std::cout << "Open List Map Size: " << open_list_map.size() << std::endl;
    // std::cout << "Closed List Size: " << closed_list.size() << std::endl;


    // while(sgoal is not expanded and OPEN ≠ 0) -- done in setup fcn
    while(!isGoalExpanded() && !open_list.empty()){
        // remove s with the smallest [f(s) = g(s)+h(s)] from OPEN;
        // insert s into CLOSED;
        current_state_node = popOpenList();

        // std::cout << "Current State - X: " << current_state_node.node_pose[0] 
        //         << ", Y: " << current_state_node.node_pose[1] 
        //         << ", G-Value: " << current_state_node.g 
        //         << ", H-Value: " << current_state_node.h << std::endl;

        // for every successor s’ of s such that s’ not in CLOSED
        for (int i = 0; i < NUMOFDIRS; i++){
            // update s' location
            // std::cout << state_prime.node_pose[0] << "\n";
            state_prime.node_pose[0] = current_state_node.node_pose[0] + dX[i];
            state_prime.node_pose[1] = current_state_node.node_pose[1] + dY[i]; 
            state_prime.parent = &closed_list[current_state_node.node_pose];
            if (!isStateValid(state_prime)){continue;}
            // if g(s’) > g(s) + c(s,s’)
            if (closed_list.find(state_prime.node_pose) == closed_list.end() &&
                getG(state_prime.node_pose) > current_state_node.g + cost){
                // g(s’) = g(s) + c(s,s’);
                // insert s’ into OPEN;
                insertIntoOpenList(current_state_node, state_prime); 
            }
        }
    }
    return;
}

void AStar::backTracePath(){
        path.push_front(closed_list[goal_state].node_pose);
        // std::cout << "Pose - X: " << closed_list[goal_state].node_pose[0] 
        //           << ", Y: " << closed_list[goal_state].node_pose[1] << std::endl;

        // init Node obj to iterate with
        Node* mostRecentNode;
        
        mostRecentNode = closed_list[goal_state].parent;
        
        // push node to the top of the stack
        path.push_front(mostRecentNode->node_pose);
        
        while (mostRecentNode->parent->parent != nullptr){
            // assign the parent of the mostRecentNode to become the Node
            mostRecentNode = mostRecentNode->parent;
            path.push_front(mostRecentNode->node_pose);
        }
    }
 