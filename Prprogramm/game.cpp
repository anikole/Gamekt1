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
        Character bobic("Start_Location", START_X, START_Y);
        Door door1("Start_Location");
        Chests chest1("Start_Location", door1.Door_x, door1.Door_y, 
            bobic.Character_x, bobic.Character_y, command);
        

        cout << "\t=== КАРТА ===\n";
        cout << "-------НАЧАЛЬНАЯ ЛОКАЦИЯ-------\n";
        cout << "Здоровье : " << bobic.health << "\n";
        
        // Создаем сущность первой локации и саму локацию
        Location StartLocation;
        StartLocation.printForm(bobic.Character_x, bobic.Character_y, 
            chest1.Chests_x, chest1.Chests_y, door1.Door_x, door1.Door_y);

        while(command != "STOP" && bobic.Character_live != 0)
        {
            cout << "Введите команду ( или STOP для выхода )\n";
            cin >> command;

            if (command == "Up" || command == "UP" || command == "up")
            {
                bobic.MoveUp(1);
                StartLocation.printForm(bobic.Character_x, bobic.Character_y, 
                    chest1.Chests_x, chest1.Chests_y, door1.Door_x, door1.Door_y);
            }

            if (command == "Down" || command == "DOWN" || command == "down")
            {
                bobic.MoveDown(1);
                StartLocation.printForm(bobic.Character_x, bobic.Character_y,
                    chest1.Chests_x, chest1.Chests_y, door1.Door_x, door1.Door_y);
            }

            if (command == "Left" || command == "LEFT" || command == "left")
            {
                bobic.MoveLeft(1);
                StartLocation.printForm(bobic.Character_x, bobic.Character_y, 
                    chest1.Chests_x, chest1.Chests_y, door1.Door_x, door1.Door_y);
            }
            
            if (command == "Right" || command == "RIGHT" || command == "right")
            {
                bobic.MoveRight(1);
                StartLocation.printForm(bobic.Character_x, bobic.Character_y, 
                    chest1.Chests_x, chest1.Chests_y, door1.Door_x, door1.Door_y);
            }

        }
    }

    return 0;
}