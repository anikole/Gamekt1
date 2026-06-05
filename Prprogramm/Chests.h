#ifndef CHESTS_H
#define CHESTS_H

#include <string> 
#include <vector>

#include "Potions.h"
#include "Inventory.h"

class Chests
{
public:
    Chests(int Door_x, int Door_y);

    void check_Collision(int Character_x, int Character_y, 
        std::string& command, Inventory& player_inventory);

    std::vector <Potions> Chests_reward = {};
    int Chests_x;
    int Chests_y;
    int Chests_ID;
};

#endif