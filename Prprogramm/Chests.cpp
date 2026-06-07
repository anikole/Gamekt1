#include <iostream>
#include <random>
#include <vector>

#include "Chests.h"
#include "Location.h"
#include "Character.h"
#include "Door.h"
#include "Potions.h"
#include "Inventory.h"
#include "BrainBreaker.h"

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

    is_open = coin(gen);

    // Генерируем х в отрезках : 1-3 и 5-6 
    if (coin(gen) == 0) {
        uniform_int_distribution<> distr_x(1, 5);
        Chests_x = distr_x(gen);
    } else {
        uniform_int_distribution<> distr_x(7, 10);
        Chests_x = distr_x(gen);
    }

    // Генерируем у в отрезках : 1-3 и 5-6
    if (coin(gen) == 0) {
        uniform_int_distribution<> distr_y(1, 3);
        Chests_y = distr_y(gen);
    } else {
        uniform_int_distribution<> distr_y(5, 6);
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


void Chests::check_Collision(Character& player, 
    string& command, Inventory& player_inventory, int location_count)
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> coin(0, 1);

    if(Chests_x == player.Character_x && Chests_y == player.Character_y)
    {
        cout << "\nВы нашли сундук! \nХотите его открыть? (Y/N): ";
        cin >> command;

        if (have_treasures)
        {
            cout << "\nПохоже, что кто-то уже забрал награду.\n";
            return;
        }

        if(command == "Y" || command == "YES" || command == "yes" || command == "Yes")
        {
            bool can_take_reward = false;

            if(is_open)
                can_take_reward = true;
            else
            {
                cout << "\n Замок не поддается, с сундуком что-то не так. \n";
                BrainBreaker puzzle;
                if (puzzle.start_bb_for_chests(player) == true) 
                {
                    can_take_reward = true;
                    is_open = true; 
                }
            }

            if (can_take_reward)
            {
                have_treasures = true;

                if (location_count == 5)
                {
                    Potions last_treasure;
                    last_treasure.Potions_ID = 999;
                    last_treasure.health_add = 0; 
                    last_treasure.Potion_Name = " ∼ Кубок победителя ∼ ";
                    last_treasure.treasure = true;
                    player_inventory.add_potion(last_treasure);
                
                    cout << "\n=============================================";
                    cout << "\n[ПОБЕДА] Вы открыли финальный сундук!";
                    cout << "\nВы нашли легендарный артефакт: " << last_treasure.Potion_Name;
                    cout << "\n=============================================\n";
                }
                else if (coin(gen) == 0) 
                {
                    cout << "Похоже, этот сундук пуст... \n"; 
                }
                else 
                {
                    Potions found_potion; 
                    player_inventory.add_potion(found_potion); 

                    cout << "Вы нашли '" << found_potion.Potion_Name << "' (Лечит: " 
                        << found_potion.health_add << ") и положили в инвентарь!\n";
                }
            }
        }
        else if(command == "N" || command == "NO" || command == "no" || command == "No") 
        {
            cout << "Вы решили пройти мимо сундука.\n";
        }
    }

}