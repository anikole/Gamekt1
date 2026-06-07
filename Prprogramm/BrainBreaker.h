#ifndef BRAINBREAKER_H
#define BRAINBREAKER_H

#include <string> 

class Character;

class BrainBreaker
{
public:
    BrainBreaker();
    int type_of_bb;
    bool start_bb_for_chests(Character& player);
    bool start_bb_for_door(Character& player);

private:
    bool play_riddle(Character& player);
    bool answer_math_quiz(Character& player);
    bool guess_number(Character& player);
    bool d_answer_math_quiz(Character& player);
    bool d_play_riddle(Character& player);
    bool d_guess_number(Character& player);
};

#endif 