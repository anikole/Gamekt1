#include <iostream>
#include <random>

#include "Location.h"
#include "Character.h"
#include "Chests.h"
#include "Door.h"
#include "BrainBreaker.h"

using namespace std;

Door::Door(int location_count)
{
    // Создаем генератор рандомных чисел
    static random_device rd;
    static mt19937 gen(rd());

    // Создаем генератор броска монетки (50/50)
    std::uniform_int_distribution<> coin(0, 1);

    /* Генерируем х в диапазонах 1-3 и 5-6 для того, 
    чтобы координаты игрока не совпали с координатами двери */
    if (coin(gen) == 0) {
        std::uniform_int_distribution<> distr_x(1, 5);
        Door_x = distr_x(gen);
    } else {
        std::uniform_int_distribution<> distr_x(7, 10);
        Door_x = distr_x(gen);
    }

    /* Генерируем у в диапазонах 1-5 и 7-10 для того, 
    чтобы координаты игрока не совпали с координатами двери */
    if (coin(gen) == 0) {
        std::uniform_int_distribution<> distr_y(1, 3);
        Door_y = distr_y(gen);
    } else {
        std::uniform_int_distribution<> distr_y(5, 6);
        Door_y = distr_y(gen);
    }
}
bool Door::check_collision_door(Character& player, string& command)
{
    if (Door_x == player.Character_x && Door_y == player.Character_y)
    {
        door_is_open = false;

        if(door_is_open == false)
        {
            cout << "\nВы хотите перейти в следущую локацию ? \n";
            cin >> command;
            
            if(command == "Y" || command == "YES" || command == "yes" || command == "Yes")
            {
                BrainBreaker puzzle;
                if (puzzle.start_bb_for_door(player) == true)
                {
                    door_is_open = true;
                    cout << "\n Дверь наконц-таки поддалась и вы успешно перешли в другую комнату!\n";
                    return true;
                }
                else
                    return false;
            }
            else if(command == "N" || command == "NO" || command == "no" || command == "No")
            {
                cout << "\nВы решили побыть в текущей комнате еще немного.\n";
                return false;
            }
            else
            {
                cout << "\nДверь не поняла вас и не открылась. \n";
                return false;
            }
            return false;
        }
        return false;
    }
    else
        return false;
}