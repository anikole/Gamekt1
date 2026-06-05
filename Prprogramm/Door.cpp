#include <iostream>
#include <random>

#include "Location.h"
#include "Character.h"
#include "Chests.h"
#include "Door.h"

using namespace std;

Door::Door(string My_Location)
{
    // Создаем генератор рандомных чисел
    static random_device rd;
    static mt19937 gen(rd());

    // Создаем генератор броска монетки (50/50)
    std::uniform_int_distribution<> coin(0, 1);

    /* Генерируем х в диапазонах 1-3 и 5-6 для того, 
    чтобы координаты игрока не совпали с координатами двери */
    if (coin(gen) == 0) {
        std::uniform_int_distribution<> distr_x(1, 3);
        Door_x = distr_x(gen);
    } else {
        std::uniform_int_distribution<> distr_x(5, 6);
        Door_x = distr_x(gen);
    }

    /* Генерируем у в диапазонах 1-5 и 7-10 для того, 
    чтобы координаты игрока не совпали с координатами двери */
    if (coin(gen) == 0) {
        std::uniform_int_distribution<> distr_y(1, 5);
        Door_y = distr_y(gen);
    } else {
        std::uniform_int_distribution<> distr_y(7, 10);
        Door_y = distr_y(gen);
    }
}