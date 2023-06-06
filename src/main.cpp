#include "constants.h"
#include "display.cpp"
#include "include/raylib.h"
#include "input.cpp"
#include "render.cpp"
#include "solve.cpp"
#include <iostream>
#include <vector>

int main() {

  InitWindow(screenWidth, screenHeight, "Calculator");
  SetTargetFPS(60);

  // Initalize objects

  Solver solver;

  // Initialize variables
  Display display;

  while (!WindowShouldClose()) {
    display.update();

    if (display.readyToSolve) {
      std::string problem = display.getProblem();
      // display.radians
      try {
        std::string expr = std::to_string(solver.solve(problem));
        display.solution(expr);
      } catch (int errorCode) {
        display.readyToSolve = false;
        cout << "Error #: " + errorCode;
        display.solution("Error: " + errorCode);
      }
    }

    BeginDrawing();
    ClearBackground(WHITE);

    display.draw();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
