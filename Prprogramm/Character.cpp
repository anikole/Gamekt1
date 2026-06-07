#include <iostream>
#include <vector>

#include "Character.h"
#include "Location.h"
#include "Chests.h"
#include "Potions.h"

using namespace std;

Character::Character( int start_x,int start_y, 
    string command) 
{
    Character_x = start_x;  
    Character_y = start_y;
    Character_health = 100;
    Character_live = 1;
    vector <Potions> inventory = {};

}

void Character::MoveUp(int steps)
{
    if (Character_y - steps > 0)
        Character_y--;
    else
        cout << "Бро, тут стенка\n";
}

void Character::MoveDown(int steps)
{
    if (Character_y + steps < 7)
        Character_y++;
    else
        cout << "Бро, тут стенка\n";
}
void Character::MoveRight(int steps)
{
    if (Character_x + steps < 11)
        Character_x++;
    else
        cout << "Бро, тут стенка\n";
}
void Character::MoveLeft(int steps)
{
    if (Character_x - steps > 0)
        Character_x--;
    else
        cout << "Бро, тут стенка\n";
}
