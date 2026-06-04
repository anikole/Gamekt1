#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include <string>
using namespace std;

class Location
{
private:
    long  ID_Location;
    string Form[8][12];
public:
    void printForm(int Character_x, int Character_y);
};
#endif