#include "constants.h"
#include "include/raylib.h"
#include <iostream>
#include <vector>

// Draws user input, errors, and solutions
void DrawDisplay(std::vector<std::string> history, std::string answer = "") {
  DrawText(history.back().c_str(), (int)textDisplay.x + 5,
           (int)textDisplay.y + 8, 40, BLACK);
  for (int i = 0; i < history.size() - 1; i++) {
    DrawText(history[i].c_str(), (int)textDisplay.x + 5,
             (int)textDisplay.y - 24 * (history.size() - i - 1), 24, GRAY);
  }
}
