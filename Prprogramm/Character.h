#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <vector>

#include "Potions.h"

class Character
{
public:
    Character(std::string Location, int start_x,int start_y, 
        std::string command);

    bool Character_live;
    int Character_health;
    std::string location;
    int Character_x;
    int Character_y;
    std::vector <Potions> inventory = {};
    
    void MoveUp(int steps);
    void MoveDown(int steps);
    void MoveRight(int steps);
    void MoveLeft(int steps);

private:
    // int damage;
    
    
};

#endif