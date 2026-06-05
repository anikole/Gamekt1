#ifndef POTIONS_H
#define POTIONS_H

#include <string> 

class Potions
{
public:
    Potions();
    Potions(int Potions_ID, int health_add, std::string Potion_Name);
    int Potions_ID;
    int health_add;
    std::string Potion_Name;

private:

};

#endif