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
bool BrainBreaker::start_bb_for_chests(Character& player)
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
        << "Ваше текущее здоровье : " << player.Character_health - 20<< "\n";
    
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
    int type_of_riddle;
    uniform_int_distribution<> distr_type_riddle(1, 5);
    type_of_riddle = distr_type_riddle(gen);

    if (type_of_riddle == 1)
    {
        cout << "Отгадайте загадку: Что можно увидеть с закрытыми глазами?\nОтвет (одно слово большими буквами): ";
        cin >> answer;

        if (answer == "СОН" || answer == "СНЫ" || answer == "Сновидение") 
        {
            cout << "Символы на сундуке погасли. Путь свободен!\n";
            return true;
        }
    }
    else if(type_of_riddle == 2)
    {
        cout << "Отгадайте загадку: Что может путешествовать по всему миру, всегда оставаясь в одном и том же углу? "
        << "Ответ (одно слово большими буквами) : ";
        cin >> answer;

        if (answer == "МАРКА" || answer == "Марка" ) 
        {
            cout << "Символы на сундуке погасли. Путь свободен!\n";
            return true;
        }
    }
    else if(type_of_riddle == 3)
    {
        cout << "Отгадайте загадку: Что может подниматься в гору и спускаться с нее, но при этом физически не делает ни единого шага и остается на месте?\n"
        << "Ответ (одно слово большими буквами): ";
        cin >> answer;

        if (answer == "ДОРОГА" || answer == "ТРОПА" || answer == "Дорога") 
        {
            cout << "Символы на сундуке погасли. Путь свободен!\n";
            return true;
        }
    }
    else if(type_of_riddle == 4)
    {
        cout << "Отгадайте загадку:  Если вы владеете этим, вы хотите этим поделиться. \nНо если вы поделитесь этим с кем-то другим, вы этим больше не владеете. О чем речь?\n"
        <<"\nОтвет (одно слово большими буквами): ";
        cin >> answer;

        if (answer == "СЕКРЕТ" || answer == "Секрет" ) 
        {
            cout << "Символы на сундуке погасли. Путь свободен!\n";
            return true;
        }
    }
    else if(type_of_riddle == 5)
    {
        cout << "Отгадайте загадку: Что всегда находится прямо перед нами, принадлежит нашему завтрашнему дню, но мы никогда не сможем это увидеть?"
        <<"\nОтвет (одно слово большими буквами): ";
        cin >> answer;

        if (answer == "БУДУЩЕЕ" || answer == "Будущее" ) 
        {
            cout << "Символы на сундуке погасли. Путь свободен!\n";
            return true;
        }
    }

    int damage = 15;
    player.Character_health -= damage;
    cout << "Замок заискрился. Вы почувствовали удар током.\n" 
    << "Ваше здоровье было снижено. \nВашее текущее здоровье : " 
    << player.Character_health<< "\n";
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
    << "\nВаше текущее здоровье : " << player.Character_health<< "\n";
    if (player.Character_health <= 0)
    {
        player.Character_live = 0;
        cout << "\nВы погибли от взрыва сундука...";
    }
    return false;
}

bool BrainBreaker::start_bb_for_door(Character& player)
{
    cout << "\nПохоже эта дверь закрыта каким-то механизмом.\n";

    // В зависимости от типа запускаем нужную мини-игру
    switch (type_of_bb)
    {
        case 1: return d_answer_math_quiz(player);
        case 2: return d_play_riddle(player);
        case 3: return d_guess_number(player);
        default: return false;
    }
}
// 1.Головоломка для двери
bool BrainBreaker::d_answer_math_quiz(Character& player)
{
    uniform_int_distribution<> distr_num_d(10, 50);
    int a = distr_num_d(gen);
    int b = distr_num_d(gen);
    int correct_answer = a - b;
    int player_answer;

    cout << "Решите уравнение, чтобы снять замок: " << a << " - " << b << " = ?\nОтвет: ";
    cin >> player_answer;

    if (player_answer == correct_answer) 
    {
        cout << "Раздался щелчок! Замок открылся.\n";
        return true;
    }
    int damage = 10;
    player.Character_health -= damage;
    cout << "Неверно! Из под двери высунулась когтистая лапа и расцарапала вас.\nВаше здоровье было снижено.\n"
        << "Ваше текущее здоровье : " << player.Character_health - damage << "\n";
    
    if (player.Character_health <= 0)
    {
        player.Character_live = 0;
        cout << "\nВы погибли серьезных увечий...";
    }
    return false;
}
// 2.Головоломка для двери
bool BrainBreaker::d_play_riddle(Character& player)
{
    string answer;
    int type_of_riddle;
    uniform_int_distribution<> distr_type_riddle_d(1, 5);
    type_of_riddle = distr_type_riddle_d(gen);

    if (type_of_riddle == 1)
    {
        cout << "Отгадайте загадку: Что настолько хрупкое и ранимое, что стоит вам только произнести его имя, как вы тут же его безвозвратно разрушите?"
        <<"\nОтвет (одно слово большими буквами): ";
        cin >> answer;

        if (answer == "ТИШИНА" || answer == "Тишина" ) 
        {
            cout << "В замке что-то щелкнуло. Путь свободен!\n";
            return true;
        }
    }
    else if(type_of_riddle == 2)
    {
        cout << "Отгадайте загадку: Что может подниматься прямо к небу, лететь по воздуху, не имея крыльев, и заставлять людей плакать, хотя у него нет никаких чувств?"
        << "Ответ (одно слово большими буквами) : ";
        cin >> answer;

        if (answer == "ДЫМ" || answer == "Дым" ) 
        {
            cout << "В замке что-то щелкнуло. Путь свободен!\n";
            return true;
        }
    }
    else if(type_of_riddle == 3)
    {
        cout << "Отгадайте загадку: Этот невидимый предмет разговаривает на всех языках мира, легко повторяет любые сложные слова, но никогда не начинает разговор первым. Что это?\n"
        << "Ответ (одно слово большими буквами): ";
        cin >> answer;

        if (answer == "ЭХО" || answer == "Эхо" ) 
        {
            cout << "В замке что-то щелкнуло. Путь свободен!\n";
            return true;
        }
    }
    else if(type_of_riddle == 4)
    {
        cout << "Отгадайте загадку:  Чем больше вы забираете из этого объекта, тем больше и шире он становится. Что это?\n"
        <<"\nОтвет (одно слово большими буквами): ";
        cin >> answer;

        if (answer == "ЯМА" || answer == "Яма" ) 
        {
            cout << "В замке что-то щелкнуло. Путь свободен!\n";
            return true;
        }
    }
    else if(type_of_riddle == 5)
    {
        cout << "Отгадайте загадку: Что всегда находится прямо перед нами, принадлежит нашему завтрашнему дню, но мы никогда не сможем это увидеть?"
        <<"\nОтвет (одно слово большими буквами): ";
        cin >> answer;

        if (answer == "БУДУЩЕЕ" || answer == "Будущее" ) 
        {
            cout << "В замке что-то щелкнуло. Путь свободен!\n";
            return true;
        }
    }

    int damage = 15;
    player.Character_health -= damage;
    cout << "Замок заискрился. Вы почувствовали удар током.\n" 
    << "Ваше здоровье было снижено. \nВашее текущее здоровье : " 
    << player.Character_health << "\n";
    if (player.Character_health <= 0)
    {
        player.Character_live = 0;
        cout << "\nВы погибли от сильного удара током...";
    }
    return false;
}
// 3. Головоломка для двери
bool BrainBreaker::d_guess_number(Character& player)
{
    uniform_int_distribution<> distr_secret_d(1, 10);
    int secret = distr_secret_d(gen);
    int guess;
    int attempts = 3;

    cout << "Взломайте шифр! Угадайте число от 1 до 10. У вас " << attempts << " попытки.\n";

    while (attempts > 0) {
        cout << "Ваш вариант: ";
        cin >> guess;

        if (guess == secret) {
            cout << "Вы угадали комбинацию! Дверь открыта.\n";
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
    cout << "Из двери потекла ядовитая жидкость."
    <<"\nВаше здоровье было снижено."
    << "\nВаше текущее здоровье : " << player.Character_health<< "\n";
    if (player.Character_health <= 0)
    {
        player.Character_live = 0;
        cout << "\nВы утонули...";
    }
    return false;
}