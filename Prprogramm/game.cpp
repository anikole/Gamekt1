#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>

#include "Character.h"
#include "Location.h"
#include "Chests.h"
#include "Door.h"

using namespace std;

void save_game(int loc, int px, int py, int hp, int sx, int sy, int sloc, 
               int dx, int dy, int cx, int cy) 
{
    ofstream save_file("save.txt"); 
    if (save_file.is_open()) 
    {
        // Записываем всё в одну строку через пробел
        save_file << loc << " " << px << " " << py << " " << hp << " " 
                  << sx << " " << sy << " " << sloc << " "
                  << dx << " " << dy << " " << cx << " " << cy;
        save_file.close();
        cout << "\n[СИСТЕМА] Игра успешно сохранена!\n";
    } 
    else 
    {
        cout << "\n[ОШИБКА] Не удалось создать файл сохранения.\n";
    }
}


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
        Inventory my_inventory;
        Character player1(START_X, START_Y, command);
        
        int spawn_x = START_X;
        int spawn_y = START_Y;
        int spawn_location = 1;

        // Переменные для временного хранения координат из файла
        int saved_dx = 0, saved_dy = 0, saved_cx = 0, saved_cy = 0;
        bool is_loaded = false;

        // ПРОВЕРКА НАЛИЧИЯ СОХРАНЕНИЯ
        ifstream load_file("save.txt");
        if (load_file.is_open()) 
        {
            string choice;
            cout << "\nНайдено сохранение! Желаете продолжить старую игру? (Y/N): ";
            cin >> choice;
            
            if (choice == "Y" || choice == "y" || choice == "YES" || choice == "yes" || choice == "Yes") 
            {
                // Считываем ВСЕ данные в строгом порядке
                load_file >> location_count >> player1.Character_x >> player1.Character_y 
                          >> player1.Character_health >> spawn_x >> spawn_y >> spawn_location
                          >> saved_dx >> saved_dy >> saved_cx >> saved_cy;
                
                if (location_count == 5)
                    name_of_location = "ФИНАЛЬНАЯ ЛОКАЦИЯ";
                else
                    name_of_location = "ЛОКАЦИЯ №" + to_string(location_count);
                    
                is_loaded = true;
                cout << "\n[СИСТЕМА] Сохранение загружено!\n";
            }
            load_file.close();
        }

        // Инициализируем объекты двери и сундука
        Door door1(location_count);
        Chests chest1(door1.Door_y, door1.Door_x);
        
        // ЕСЛИ ИГРА ЗАГРУЖЕНА: принудительно перезаписываем сгенерированные координаты
        if (is_loaded)
        {
            door1.Door_x = saved_dx;
            door1.Door_y = saved_dy;
            chest1.Chests_x = saved_cx;
            chest1.Chests_y = saved_cy;
        }
        else if (location_count == 5) 
        {
            // Стандартная настройка для 5 уровня, если начали новую игру и сразу переместились
            door1.Door_x = 5; door1.Door_y = 1;
            chest1.Chests_x = 5; chest1.Chests_y = 4;
        }

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

            // ПЕРЕХВАТ ВЫХОДА ДЛЯ СОХРАНЕНИЯ
            if (command == "STOP" || command == "stop" || command == "Stop")
            {
                // Передаем текущие координаты игрока, спавнпоинта, двери и сундука
                save_game(location_count, player1.Character_x, player1.Character_y, 
                          player1.Character_health, spawn_x, spawn_y, spawn_location,
                          door1.Door_x, door1.Door_y, chest1.Chests_x, chest1.Chests_y);
                
                break; 
            }

            if (command == "Up" || command == "UP" || command == "up")
            // ... (дальше ваш код движения)


            if (command == "Up" || command == "UP" || command == "up" || command == "U"|| command == "u")
                player1.MoveUp(1);
            
            if (command == "Down" || command == "DOWN" || command == "down" || command == "D"|| command == "d")
                player1.MoveDown(1);

            if (command == "Left" || command == "LEFT" || command == "left"|| command == "L"|| command == "l")
                player1.MoveLeft(1);

            if (command == "Right" || command == "RIGHT" || command == "right" || command == "R"|| command == "r")
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