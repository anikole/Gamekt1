#include <iostream>
#include <random>

#include "Character.h"
#include "Chests.h"
#include "Potions.h"
#include "Inventory.h"

using namespace std;

Potions::Potions()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    uniform_int_distribution<> distr_id(1, 100);
    uniform_int_distribution<> distr_heal(20, 30);

    Potions_ID = distr_id(gen);
    health_add = distr_heal(gen);

    // Создаем список возможных названий для зелий
    std::vector<std::string> names_pool = {
        "Малое зелье лечения",
        "Большое зелье здоровья",
        "Эликсир бодрости",
        "Древнее лечебное снадобье",
        "Настойка на целебных травах",
        "Зелье восстановления сил"
    };

    // Генерируем случайный индекс (от 0 до размера списка минус 1)
    std::uniform_int_distribution<> distr_name(0, names_pool.size() - 1);
    int random_index = distr_name(gen);

    // Присваиваем случайное имя из списка
    Potion_Name = names_pool[random_index];
}
