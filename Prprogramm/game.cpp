#include <stdio.h>
#include <iostream>
#include <vector>

#include "Character.h"
#include "Location.h"
#include "Chests.h"
#include "Door.h"

using namespace std;

int START_X = 4;
int START_Y = 6;

int main(void)
{
    string command;
    cout << "Напишите START для начала игры : \n";
    cin >> command;

    if (command == "START" || command == "start" || command == "Start")
    {
        // Создаем сущности для первой локации
        Inventory my_inventory;
        Character bobic("Start_Location", START_X, START_Y, command);
        Door door1("Start_Location");
        Chests chest1(door1.Door_y, door1.Door_x);

        cout << "\t=== КАРТА ===\n";
        cout << "-------НАЧАЛЬНАЯ ЛОКАЦИЯ-------\n";
        cout << "Здоровье : " << bobic.health << "\n";
        
        // Создаем сущность первой локации и саму локацию
        Location StartLocation;
        StartLocation.printForm(bobic.Character_y, bobic.Character_x, 
            chest1.Chests_y, chest1.Chests_x, door1.Door_x, door1.Door_y);

        while(command != "STOP" && bobic.Character_live != 0)
        {
            cout << "Введите команду ( или STOP для выхода )\n";
            cin >> command;

            if (command == "Up" || command == "UP" || command == "up")
            {
                bobic.MoveUp(1);
            }

            if (command == "Down" || command == "DOWN" || command == "down")
            {
                bobic.MoveDown(1);
            }

            if (command == "Left" || command == "LEFT" || command == "left")
            {
                bobic.MoveLeft(1);
            }
            
            if (command == "Right" || command == "RIGHT" || command == "right")
            {
                bobic.MoveRight(1);
            }

            if (command == "INVENTORY" || command == "inventory" || command == "Inventory" 
                || command == "INV" || command == "Inv" || command == "inv")
            {
                my_inventory.check_inventory();
                continue;
            }

            // Проверяем, наступил ли игрок на сундук
            chest1.check_Collision(bobic.Character_x, bobic.Character_y, command, my_inventory);
            // Перерисовываем карту с учетом новых (или отброшенных сундуком) координат
            StartLocation.printForm(bobic.Character_y, bobic.Character_x, 
                chest1.Chests_y, chest1.Chests_x, door1.Door_x, door1.Door_y);
        }
    }

    return 0;
}