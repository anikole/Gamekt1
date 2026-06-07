#ifndef CHEST_H
#define CHEST_H

#include <random> 

#include "Location.h"
#include "Chests.h"
#include "BrainBreaker.h"

class Door
{
public:
    Door(int location_count);

    int location_count;
    int Door_x;
    int Door_y;
    bool door_is_open;

    bool check_collision_door(Character& player, std::string& command);
};

#endif