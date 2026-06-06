#include <iostream>

#include "Character.h"
#include "Chests.h"
#include "Potions.h"
#include "Inventory.h"

using namespace std;

Inventory::Inventory()
{

}
void Inventory::add_potion (const Potions& potion)
{
    items.push_back(potion);
}
void Inventory::check_inventory()
{
    std::cout << "\n=== ВАШ ИНВЕНТАРЬ ===" << std::endl;
    
    if (items.empty()) {
        std::cout << "Ваша сумка пуста..." << std::endl;
    } else {
        for (int i = 0; i < items.size(); i++) 
        {
            std::cout << i + 1 << ". " << items[i].Potion_Name 
                      << " [ID: " << items[i].Potions_ID 
                      << "] (Лечит: " << items[i].health_add << " Здоровья)" << std::endl;
        }
    }
    std::cout << "=====================\n" << std::endl;
}
void Inventory::use_potion(int index, Character& bobic )
{
    for (int i = 0; i < items.size(); i++) 
        {
            if(items[i].Potions_ID == index - 1)
            {
                bobic.Character_health += items[index].health_add;
                cout << "Вы восстановили здоровье на " << items[i].health_add 
                << "\n Ваше текущее здоровье : " << bobic.Character_health << "\n";

                bobic.Character_health += items[index].health_add;
            }
        }
}