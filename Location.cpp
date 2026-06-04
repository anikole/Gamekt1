#include <iostream>
#include <vector>

#include "Location.h"
#include "Character.h"

using namespace std;

void Location::printForm(int Character_x, int Character_y)
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
                    else if (i == Character_y && j == Character_x)
                        Form[i][j] = "@";
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
