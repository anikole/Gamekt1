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
        Character player("Start_Location", START_X, START_Y, command);
        Door door1("Start_Location");
        Chests chest1(door1.Door_y, door1.Door_x);

        cout << "\t=== КАРТА ===\n";
        cout << "-------НАЧАЛЬНАЯ ЛОКАЦИЯ-------\n";
        cout << "Здоровье : " << player.Character_health << "\n";
        
        // Создаем сущность первой локации и саму локацию
        Location StartLocation;
        StartLocation.printForm(player.Character_y, player.Character_x, 
            chest1.Chests_y, chest1.Chests_x, door1.Door_x, door1.Door_y);

        while(command != "STOP" && player.Character_live != 0)
        {
            cout << "Введите команду ( или STOP для выхода )\n";
            cin >> command;

            if (command == "Up" || command == "UP" || command == "up")
            {
                player.MoveUp(1);
            }

            if (command == "Down" || command == "DOWN" || command == "down")
            {
                player.MoveDown(1);
            }

            if (command == "Left" || command == "LEFT" || command == "left")
            {
                player.MoveLeft(1);
            }
            
            if (command == "Right" || command == "RIGHT" || command == "right")
            {
                player.MoveRight(1);
            }

            // Проверяем инвентарь и пьем зелье
            if (command == "INVENTORY" || command == "inventory" || command == "Inventory" 
                || command == "INV" || command == "Inv" || command == "inv")
            {
                my_inventory.check_inventory();

                cout << "\nВы хотите использовать зелье? (Y/N) : ";
                cin >> command;
                if(command == "Y" || command == "YES" || command == "yes" || command == "Yes")
                {
                    if (!my_inventory.items.empty()) 
                    {
                        cout << "\nВведите номер зелья, которое хотите выпить: ";
                        int choice;
                        cin >> choice;
            
                        my_inventory.use_potion(choice, player); 
                    }
                    else
                        cout << "\nВ сумке нет зелий - вам нечего пить.\n";
                    continue;
                }
                else if(command == "N" || command == "NO" || command == "no" || command == "No")
                    cout << "\nВы решили оставить зелье на потом.";
                    
                continue;
            }

            // Проверяем, наступил ли игрок на сундук
            chest1.check_Collision(player, command, my_inventory);
            // Перерисовываем карту с учетом новых (или отброшенных сундуком) координат
            StartLocation.printForm(player.Character_y, player.Character_x, 
                chest1.Chests_y, chest1.Chests_x, door1.Door_x, door1.Door_y);
        }
    }

    return 0;
}