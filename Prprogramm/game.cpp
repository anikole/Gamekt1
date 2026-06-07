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
string name_of_location = "НАЧАЛЬНАЯ ЛОКАЦИЯ";
int location_count = 1;

int main(void)
{
    string command;
    cout << "Напишите START для начала игры : \n";
    cin >> command;

    if (command == "START" || command == "start" || command == "Start")
    {
        // Создаем сущности для первой локации
        Inventory my_inventory;
        Character player1( START_X, START_Y, command);
        Door door1(location_count);
        Chests chest1(door1.Door_y, door1.Door_x);

        cout << "\t=== КАРТА ===\n";
        cout << "-------"<< name_of_location <<"-------\n";
        cout << "\nЗдоровье : " << player1.Character_health << "\n\n";
        
        // Создаем сущность первой локации и саму локацию
        Location StartLocation;
        StartLocation.printForm(player1.Character_y, player1.Character_x, 
            chest1.Chests_y, chest1.Chests_x, door1.Door_y, door1.Door_x);

        while(command != "STOP" && player1.Character_live != 0)
        {
            cout << "Введите команду ( или STOP для выхода )\n";
            cin >> command;

            if (command == "Up" || command == "UP" || command == "up")
                player1.MoveUp(1);
            
            if (command == "Down" || command == "DOWN" || command == "down")
                player1.MoveDown(1);

            if (command == "Left" || command == "LEFT" || command == "left")
                player1.MoveLeft(1);

            if (command == "Right" || command == "RIGHT" || command == "right")
                player1.MoveRight(1);
    
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
            
                        my_inventory.use_potion(choice, player1); 
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
            chest1.check_Collision(player1, command, my_inventory, location_count);
            
            // Создаем новую локацию, если игрок прошел головоломку на двери
            if(door1.check_collision_door(player1, command) == true )
            { 
                
                if(location_count == 5 )
                {
                    cout << "\n==============================\n";
                    cout << "\nВы прошли игру!\n";
                    cout << "\n==============================\n";
                    player1.Character_live = 0;
                    continue;
                }

                location_count ++;
                cout << "\n--- Вы перешли в новую комнату! ---\n";
                // Увеличиваем счетчик локации

                if (location_count == 5)
                {
                    name_of_location = "ФИНАЛЬНАЯ ЛОКАЦИЯ";

                    player1.Character_x = 5;
                    player1.Character_y = 6;
                    door1.Door_x = 5;
                    door1.Door_y = 1;
                    chest1.Chests_x = 5;
                    chest1.Chests_y = 4;
                }

                else
                {
                    name_of_location = "ЛОКАЦИЯ №" + to_string(location_count);

                    // Задаем снова стартовые координаты персонажу
                    player1.Character_x = START_X;
                    player1.Character_y = START_Y;

                    // Пересоздаем дверь и сундук (старые объекты заменяются новыми)
                    door1 = Door(location_count); 
                    chest1 = Chests(door1.Door_y, door1.Door_x);
                }
                
                cout << "\t=== КАРТА ===\n";
                cout << "------- " << name_of_location << " -------\n";
                cout << "Здоровье : " << player1.Character_health << "\n";

                // Перерисовываем карту 
                StartLocation.printForm(player1.Character_y, player1.Character_x, 
                    chest1.Chests_y, chest1.Chests_x, door1.Door_y, door1.Door_x);
            }
            else
            {
                StartLocation.printForm(player1.Character_y, player1.Character_x, 
                    chest1.Chests_y, chest1.Chests_x, door1.Door_y, door1.Door_x);
            }
        }
    }

    return 0;
}