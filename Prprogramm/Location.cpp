#include <iostream>
#include <vector>

#include "Location.h"
#include "Character.h"
#include "Chests.h"
#include "Door.h"

using namespace std;

void Location::printForm(int Character_x, int Character_y, 
    int Chests_x, int Chests_y, int Door_x, int Door_y)
{
    {
        for(int i = 0; i < 8; i ++)
        {
            for (int j = 0; j < 12; j ++)
                {
                    if (i == 0 || i == 7)
                        Form[i][j] = "#";
                    else if (j == 0 || j == 11)
                        Form[i][j] = "#";
                    else if (i == Character_x && j == Character_y)
                        Form[i][j] = "@";
                    else if ( i == Chests_x && j == Chests_y)
                        Form[i][j] = "C";
                    else if ( i == Door_x && j == Door_y)
                        Form[i][j] = "D";
                    else
                        Form[i][j] = ".";
                }
        }
            
        for(int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 12; j++)
            {
            cout << Form[i][j];
            }
            cout << "\n";
        }
    }
}
