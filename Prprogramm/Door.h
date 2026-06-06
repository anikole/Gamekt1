#ifndef CHEST_H
#define CHEST_H

#include <random> 

#include "Location.h"
#include "Chests.h"
#include "BrainBreaker.h"

class Door
{
public:
    Door(std::string My_Location);

    int Door_x;
    int Door_y;
};

#endif