
// function set for loading in and processing motion primitives
#include "motionPrim.hpp"

using namespace nlohmann;

void loadMotionPrimitves(std::string file_path){
    std::ifstream file;
    file.open(file_path);
    json motion_prim_blob = json::parse(file);
}
