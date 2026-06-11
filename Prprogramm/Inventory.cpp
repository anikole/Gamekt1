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
        for (size_t i = 0; i < items.size(); i++) 
        {
            std::cout << i + 1 << ". " << items[i].Potion_Name 
                      << " [ID: " << items[i].Potions_ID 
                      << "] (Лечит: " << items[i].health_add << " Здоровья)" << std::endl;
        }
    }
    std::cout << "=====================\n" << std::endl;
}
void Inventory::use_potion(int choice, Character& bobic )
{
    int target_index = choice - 1;
    if (target_index >= 0 && target_index < static_cast<int>(items.size()))
    {
        // Восстанавливаем здоровье
        bobic.Character_health += items[target_index].health_add;

        if(bobic.Character_health >= 100)
            bobic.Character_health = 100;
        
        cout << "\nВы выпили зелье и восстановили здоровье на " << items[target_index].health_add << " единиц.\n";
        cout << "Ваше текущее здоровье: " << bobic.Character_health << "\n";

        // Удаляем использованное зелье из инвентаря, чтобы его нельзя было выпить бесконечно
        items.erase(items.begin() + target_index);
    }
    else if (items[target_index].treasure == true) {
        cout << "\nЭтот предмет нельзя использовать, это ваш победный трофей!\n";
        return;
    }
    else
        cout << "\nЗелья под таким номером не существует в вашем инвентаре!\n";
}