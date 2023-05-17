#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "include/raylib.h"
#include <iostream>
#include <vector>

const int screenWidth = 800;
const int screenHeight = 450;
const Rectangle textDisplay = {(float)screenWidth / 2 - 100, 180, 225, 50};
const std::vector<std::string> buttons = {"sin", "cos", "tan"};

#endif
