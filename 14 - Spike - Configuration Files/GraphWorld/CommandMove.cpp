#include "CommandMove.h"

std::string CommandMove::Process(std::vector<std::string> input) {
    // move[n, s, e, u ... etc] if valid direction from current player location
    if (input.size() != 2) {
        return "Can't move like that! Syntax: \"move (direction)\"";
    }

    // convert any alias direction into full "key" version(n -> "north")
    std::string dir = input[1];
    std::string dirName = World::dir_check(input[1]);
    
    Location* location = world->GetLocation();
    std::map<std::string, int> directions = location->GetDirections();

    // is a valid move ?
    if (directions.count(dir)) {
        // move it!
        world->SetLocation(directions[dir]);
        return "You have moved " + dirName + " to " + world->GetLocation()->GetName();
    }
    return "Can't move " + dirName + ".";
};