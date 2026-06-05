#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include <string>

class Location
{
private:
    long  ID_Location;
    std::string Form[8][12];
public:
    void printForm(int Character_x, int Character_y,
        int Chests_x, int Chests_y, int Door_x, int Door_y);

    // void Change_Location(int Character_x, int Character_y, 
    //     int Chests_x, int Chests_y, int Door_x, int Door_y, 
    //     std::string command);
};
#endif