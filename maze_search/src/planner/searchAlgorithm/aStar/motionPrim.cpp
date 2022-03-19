
// function set for loading in and processing motion primitives
#include "motionPrim.hpp"

using namespace nlohmann;

void loadMotionPrimitves(std::string file_path, json &primitives){
    std::ifstream file;
    file.open(file_path);
    primitives = json::parse(file);
}
