#ifndef CHESTS_H
#define CHESTS_H

#include <string> 
#include <vector>

#include "Potions.h"
#include "Inventory.h"
#include "BrainBreaker.h"

class Chests
{
public:
    Chests(int Door_x, int Door_y);

    void check_Collision(Character& player, 
        std::string& command, Inventory& player_inventory);

    std::vector <Potions> Chests_reward = {};
    int Chests_x;
    int Chests_y;
    int Chests_ID;

    bool have_treasures = false;
    bool is_open;
};

#endif