#include <iostream>
#include <vector>

using namespace std;

#ifndef CHARACTER_H
#define CHARACTER_H

// class Item;

class Character
{
public:
    Character(string Location, int start_x,int start_y);

    bool Character_live = 1;
    int health;
    string location;
    int Character_x;
    int Character_y;
    
    void MoveUp(int steps);
    void MoveDown(int steps);
    void MoveRight(int steps);
    void MoveLeft(int steps);

private:
    int damage = 1;
    // std::vector<Item> inventory = {};
    
};

#endif