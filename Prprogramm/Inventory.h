#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>

#include "Potions.h"

class Character;

class Inventory
{
public:
    Inventory();
    std::vector<Potions> items;

    void add_potion(const Potions& potion);
    void check_inventory();
    void use_potion(int index, Character& bobic);
};

#endif