#include <iostream>
#include <random>

#include "Location.h"
#include "Character.h"
#include "Chests.h"
#include "Door.h"

using namespace std;

Chests::Chests(string My_Location, int Door_x, int Door_y, 
    int Character_x, int Character_y, string command)
{
    // Генератор рандомнвх чисел
    static random_device rd;
    static mt19937 gen(rd());

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
        uniform_int_distribution<> distr_y(1, Door_x);
        Chests_y = distr_y(gen);

        uniform_int_distribution<> distr_y(1, Door_y);
        Chests_y = distr_y(gen);
    }

    /*Нахождение сундука*/
    // if(Chests_x == Character_x || Chests_y == Character_y )
    // {
    //     Character_x --;
    //     Character_y --;
    //     cout << "Вы нашли сундук! \nХотите его открыть ?\nY/N";
    //     cin >> command;

    //     if(command == "Y" || command == "YES" || command == "yes" || command == "Yes")
    //     {

    //     }
    //     else if(command == "N" || command == "NO" || command == "no" || command == "No")
    //     {
            
    //     }
    // }
}