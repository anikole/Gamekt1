#include <iostream>
#include <random>
#include <vector>

#include "BrainBreaker.h"
#include "Chests.h"
#include "Location.h"
#include "Character.h"
#include "Door.h"

using namespace std;

static random_device rd;
static mt19937 gen(rd());

BrainBreaker::BrainBreaker()
{
    uniform_int_distribution<> distr_type(1, 3);
    /* Создаем рандомный тип головоломки, 
    чтобы случаным образом она определялась */
    type_of_bb = distr_type(gen);
}
bool BrainBreaker::start_bb(Character& player)
{
    cout << "\n[!] Этот сундук защищен магической головоломкой! [!]\n";
    
    // В зависимости от типа запускаем нужную мини-игру
    switch (type_of_bb)
    {
        case 1: return answer_math_quiz(player);
        case 2: return play_riddle(player);
        case 3: return guess_number(player);
        default: return false;
    }
}

// 1. Головоломка: Математический тест
bool BrainBreaker::answer_math_quiz(Character& player)
{
    uniform_int_distribution<> distr_num(10, 50);
    int a = distr_num(gen);
    int b = distr_num(gen);
    int correct_answer = a + b;
    int player_answer;

    cout << "Решите уравнение, чтобы снять замок: " << a << " + " << b << " = ?\nОтвет: ";
    cin >> player_answer;

    if (player_answer == correct_answer) 
    {
        cout << "Раздался щелчок! Замок открылся.\n";
        return true;
    }
    int damage = 20;
    player.Character_health -= damage;
    cout << "Неверно! Магическая вспышка задела вас.\nВаше здоровье было снижено.\n"
        << "Ваше текущее здоровье : " << player.Character_health - 20;
    
    if (player.Character_health <= 0)
    {
        player.Character_live = 0;
        cout << "\nВы погибли от магической вспышки...";
    }
    return false;
}

// 2. Головоломка: Текстовая загадка
bool BrainBreaker::play_riddle(Character& player)
{
    string answer;
    cout << "Отгадайте загадку: Что можно увидеть с закрытыми глазами?\nОтвет (одно слово большими буквами): ";
    cin >> answer;

    if (answer == "СОН" || answer == "СНЫ" || answer == "Сновидение") {
        cout << "Символы на сундуке погасли. Путь свободен!\n";
        return true;
    }

    int damage = 15;
    player.Character_health -= damage;
    cout << "Замок заискрился. Вы почувствовали удар током.\n" 
    << "Ваше здоровье было снижено. \nВашее текущее здоровье : " 
    << player.Character_health;
    if (player.Character_health <= 0)
    {
        player.Character_live = 0;
        cout << "\nВы погибли от сильного удара током...";
    }
    return false;
}

// 3. Головоломка: Угадай число (с 3 попыток)
bool BrainBreaker::guess_number(Character& player)
{
    uniform_int_distribution<> distr_secret(1, 10);
    int secret = distr_secret(gen);
    int guess;
    int attempts = 3;

    cout << "Взломайте шифр! Угадайте число от 1 до 10. У вас " << attempts << " попытки.\n";

    while (attempts > 0) {
        cout << "Ваш вариант: ";
        cin >> guess;

        if (guess == secret) {
            cout << "Вы угадали комбинацию! Сундук открыт.\n";
            return true;
        } else if (guess < secret) {
            cout << "Замок издает низкий гул (число больше). ";
        } else {
            cout << "Замок издает высокий писк (число меньше). ";
        }
        attempts--;
        cout << "Осталось попыток: " << attempts << "\n";
    }


    int damage = 30;
    player.Character_health -= damage;
    cout << "Попытки исчерпаны. \nСундук странно заискрился."
    << " Вы слышите очень знакомый звук шипения."
    <<"\nСундук вот-вот взорвется!\n"
    << "Вы получили урон от взрыва.\nВаше здоровье было снижено."
    << "\nВаше текущее здоровье : " << player.Character_health;
    if (player.Character_health <= 0)
    {
        player.Character_live = 0;
        cout << "\nВы погибли от взрыва сундука...";
    }
    return false;
}