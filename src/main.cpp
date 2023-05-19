#include "constants.h"
#include "include/raylib.h"
#include "input.cpp"
#include "render.cpp"
#include "solve.cpp"
#include <iostream>
#include <vector>

int main() {

  InitWindow(screenWidth, screenHeight, "Calculator");
  SetTargetFPS(60);

  // Initialize variables
  std::vector<std::string> history;
  std::vector<std::string> buttons = {"sin(", "(", ")", "delete", "1", "2", "3",
                                      "+",    "4", "5", "6",      "-", "7", "8",
                                      "9",    "*", "0", ".",      "=", "/"};
  Rectangle keypadRect = {0, (float)screenHeight * .6, screenWidth,
                          (float)screenHeight * (1 - .6)};
  int keypadKeyWrap = 4;
  history.push_back("");

  while (!WindowShouldClose()) {
    if (GetInput(history, keypadRect, buttons, keypadKeyWrap)) {
      // Solve second to last entry in history
      // because last entry is current input
      // Solve(history[history.size() - 2]);
    }

    BeginDrawing();
    ClearBackground(WHITE);

    DrawDisplay(history);

    DrawText("Calculator", (int)textDisplay.x, (int)textDisplay.y - 40, 24,
             BLACK);

    DrawRectangleLines((int)textDisplay.x, (int)textDisplay.y,
                       (int)textDisplay.width, (int)textDisplay.height,
                       DARKGRAY);

    DrawButtons(keypadRect, buttons, keypadKeyWrap);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
