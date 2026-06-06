#ifndef BRAINBREAKER_H
#define BRAINBREAKER_H

#include <string> 

class Character;

class BrainBreaker
{
public:
    BrainBreaker();
    int type_of_bb;
    bool start_bb(Character& player);

private:
    bool play_riddle(Character& player);
    bool answer_math_quiz(Character& player);
    bool guess_number(Character& player);
};

#endif 