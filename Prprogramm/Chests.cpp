#include <iostream>
#include <random>
#include <vector>

#include "Chests.h"
#include "Location.h"
#include "Character.h"
#include "Door.h"
#include "Potions.h"
#include "Inventory.h"

using namespace std;

Chests::Chests(int Door_x, int Door_y)
{
    // Генератор рандомных чисел
    static random_device rd;
    static mt19937 gen(rd());

    // Генерируем ID сундука
    uniform_int_distribution<> distr_x(1, 100);
    Chests_ID = distr_x(gen);

    // Создаем генератор монетки(50\50)
    uniform_int_distribution<> coin(0, 1);

    // Генерируем х в отрезках : 1-3 и 5-6 
    if (coin(gen) == 0) {
        uniform_int_distribution<> distr_x(1, 3);
        Chests_x = distr_x(gen);
    } else {
        uniform_int_distribution<> distr_x(5, 6);
        Chests_x = distr_x(gen);
    }

    // Генерируем у в отрезках : 1-3 и 5-6
    if (coin(gen) == 0) {
        uniform_int_distribution<> distr_y(1, 5);
        Chests_y = distr_y(gen);
    } else {
        uniform_int_distribution<> distr_y(7, 10);
        Chests_y = distr_y(gen);
    }

    /*Генерируем координаты в новом диапазоне, 
    в случае совпадения координат сундука с координатами двери*/
    if (Chests_x == Door_x || Chests_y == Door_y)
    {   
        uniform_int_distribution<> distr_door_x(1, Door_x);
        Chests_y = distr_door_x(gen);

        uniform_int_distribution<> distr_door_y(1, Door_y);
        Chests_y = distr_door_y(gen);
    }
}


void Chests::check_Collision(int Character_x, int Character_y, 
        std::string& command, Inventory& player_inventory)
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> coin(0, 1);

    if(Chests_x == Character_x && Chests_y == Character_y)
    {
        cout << "\nВы нашли сундук! \nХотите его открыть? (Y/N): ";
        cin >> command;

        if(command == "Y" || command == "YES" || command == "yes" || command == "Yes")
        {
            if (coin(gen) == 0) 
                cout << "Похоже, этот сундук пуст... \n"; 
            else 
            {
                Potions found_potion; 
                player_inventory.add_potion(found_potion); 

                cout << "Вы нашли '" << found_potion.Potion_Name << "' (Лечит: " 
                     << found_potion.health_add << ") и положили в инвентарь!\n";
            }
        }
        else if(command == "N" || command == "NO" || command == "no" || command == "No") {
            cout << "Вы решили пройти мимо сундука.\n";
        }
    }
}