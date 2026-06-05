#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>

#include "Potions.h"

class Inventory
{
public:
    Inventory();
    std::vector<Potions> items;

    void add_potion(const Potions& potion);
    void check_inventory();
};

#endif