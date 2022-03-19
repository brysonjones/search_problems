
#include "aStar.hpp"

AStar::AStar() {}

int AStar::setup(std::vector<int> robot_pose, std::vector<int> goal_pose, 
                 std::vector<int> map_bounds, std::vector<Obstacle> *obstacles) {
    
    // store start and goal poses
    current_state = robot_pose;
    goal_state = goal_pose;

    // store map info
    x_bounds.push_back(map_bounds[0]);
    x_bounds.push_back(map_bounds[1]);
    y_bounds.push_back(map_bounds[2]);
    y_bounds.push_back(map_bounds[3]);

    _obstacles = obstacles;
    updateMap();

    // initialize the starting node of the robot
    Node start_node;
    start_node.parent = nullptr;
    start_node.node_pose = {current_state[0], current_state[1], current_state[2]};
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

    // reset map
    memset(map, 0, sizeof(map)); 
    updateMap();

    // initialize the starting node of the robot
    Node start_node;
    start_node.parent = nullptr;
    start_node.node_pose = {current_state[0], current_state[1], current_state[2]};
    start_node.g = 0;
    start_node.h = 0;
    start_node.f = 0;

    // push the start node to the open list
    open_list.push(start_node);
    open_list_map[current_state] = start_node;
}

bool AStar::isStateValid(Node state){ 
    // Returns true if x and y of s_prime is in range 
    return ((state.node_pose[0] >= x_bounds[0]) && 
            (state.node_pose[0] <= x_bounds[1]) && 
            (state.node_pose[1] >= y_bounds[0]) && 
            (state.node_pose[1] <= y_bounds[1])); 
} 

int AStar::updateMap(){
    int x_loc;
    int y_loc;
    int width;
    int height;
    for (int i=0; i<_obstacles->size(); i++){
        x_loc = (*_obstacles)[i].state[0];
        y_loc = (*_obstacles)[i].state[1];
        width = (*_obstacles)[i].dims[0];
        height = (*_obstacles)[i].dims[1];
        for (int obj_i=x_loc-width/2; obj_i<x_loc+width/2; obj_i++){
            for (int obj_j=y_loc-height/2; obj_j<y_loc+height/2; obj_j++){
                map[obj_i-x_bounds[0]][obj_j-y_bounds[0]] = INT_MAX; // TODO: Define as const?
            }
        }
    }
    return 0;
}

std::vector<int> AStar::getNextState(std::vector<int> pose, int x_step, int y_step, int theta){
    // std::cout << "In -- x: " << pose[0] << ", y: " << pose[1] << ", theta: " << pose[2] << std::endl; 
    glm::vec4 _pose((float)x_step, (float)y_step, 0.0f, 1.0f);
    glm::mat4 transform = glm::mat4(1.0f);
    float angle = (float)pose[2];

    transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    _pose = transform * _pose;
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3((float)pose[0], (float)pose[1], 0.0f));
    _pose = transform * _pose;
    std::vector<int> pose_out = {(int)round(_pose.x), (int)round(_pose.y), theta};
    // std::cout << "out -- x: " << pose_out[0] << ", y: " << pose_out[1] << ", theta: " << pose_out[2] << std::endl; 

    return pose_out;
}

bool AStar::isStateObstacle(Node state){ 
    // Returns true if cell is occupied
    return map[state.node_pose[0]-x_bounds[0]][state.node_pose[1]-y_bounds[0]] >= MAX_COST; 
} 

bool AStar::isPrimitiveValid(int primNum){
    int size = primitives["mprims"][primNum]["x"].size();
    for (int i=0; i<size; i++) {
        // HACK: super messy code below
        float x = primitives["mprims"][primNum]["x"][i];
        float y = primitives["mprims"][primNum]["y"][i];
        float theta = primitives["mprims"][primNum]["theta"][i];
    }
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
    int dtheta_to_goal = abs(state.node_pose[2] - goal_state[2]);
    
    int weight = 10;  // heuristic weighting
    int h_val = weight * sqrt((dx_to_goal * dx_to_goal) 
                              + (dy_to_goal * dy_to_goal) 
                              + (dtheta_to_goal * dtheta_to_goal));
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

    // while(sgoal is not expanded and OPEN ≠ 0) -- done in setup fcn
    while(!isGoalExpanded() && !open_list.empty()){
        // remove s with the smallest [f(s) = g(s)+h(s)] from OPEN;
        // insert s into CLOSED;
        current_state_node = popOpenList();
        // for every successor s’ of s such that s’ not in CLOSED
        for (int i = 0; i<dTheta.size(); i++){            
            int theta = current_state_node.node_pose[2] + dTheta[i];
            for (int j = 0; j < NUMOFDIRS; j++){
                // update s' location
                // state_prime.node_pose[0] = current_state_node.node_pose[0] + dX[j];
                // state_prime.node_pose[1] = current_state_node.node_pose[1] + dY[j]; 
                state_prime.node_pose = getNextState(current_state_node.node_pose, dX[j], dY[j], theta);
                state_prime.parent = &closed_list[current_state_node.node_pose];
                if (!isStateValid(state_prime) || isStateObstacle(state_prime)){continue;}
                // if g(s’) > g(s) + c(s,s’)
                if (closed_list.find(state_prime.node_pose) == closed_list.end() &&
                    getG(state_prime.node_pose) > current_state_node.g + cost){
                    // g(s’) = g(s) + c(s,s’);
                    // insert s’ into OPEN;
                    insertIntoOpenList(current_state_node, state_prime); 
                }
            }
        }
    }
    return;
}

void AStar::backTracePath(){
    // TODO: Gracefully handle when no path is found
    path.push_front(closed_list[goal_state].node_pose);

    // init Node obj to iterate with
    Node* mostRecentNode;
    mostRecentNode = closed_list[goal_state].parent;

    // push node to the top of the stack
    if (mostRecentNode != nullptr){
        path.push_front(mostRecentNode->node_pose); // HACK: this segfaults when no path is found
    } else {
        std::cout << "No path found" << std::endl;
        return;
    }
    // stop loop when at second to last node
    while (mostRecentNode->parent->parent != nullptr){
        // assign the parent of the mostRecentNode to become the Node
        mostRecentNode = mostRecentNode->parent;
        path.push_front(mostRecentNode->node_pose);
    }
}
 