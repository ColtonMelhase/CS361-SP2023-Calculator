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
  std::vector<std::vector<std::string>> buttons = {
      {"tan", "cos"}, {"sin", "tan"}, {"blue"}};
  history.push_back("");

  //
  while (!WindowShouldClose()) {
    if (GetInput(history)) { // solve equation when true
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

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
