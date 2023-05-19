#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "include/raylib.h"
#include <iostream>
#include <vector>

//UI constants
const int screenWidth = 800;
const int screenHeight = 450;
const Rectangle textDisplay = {(float)screenWidth / 2 - 100, 180, 225, 50};
const std::vector<std::string> buttons = {"sin", "cos", "tan"};


//Math constants
const double e = 2.71828183;
const double pi = 3.14159265;
#endif
