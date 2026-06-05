#ifndef CHESTS_H
#define CHESTS_H

#include <random> 

#include "Character.h"
#include "Location.h"
#include "Door.h"

class Chests
{
public:
    Chests(std::string My_Location, 
        int Door_x, int Door_y, int Character_x, int Character_y, std::string command);

    int Chests_x;
    int Chests_y;
};

#endif