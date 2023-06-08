#include "constants.h"
#include "display.cpp"
#include "include/raylib.h"
#include "input.cpp"
#include "render.cpp"
#include "solve.cpp"
#include <iostream>
#include <vector>

int main() {

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "Calculator");
  MaximizeWindow();
  SetTargetFPS(60);

  // Initalize objects
  VarStorage storage;
  Solver solver(&storage);

  // Initialize variables
  Display display;

  while (!WindowShouldClose()) {
    display.update();

    if (display.readyToSolve) {
      std::string problem = display.getProblem();
      try {
        solver.radians = display.radians;   // set the mode in the solver class to the mode in the display
        solver.defineVar = display.defineVar; // set the defineVar bool to solver
        std::string expr = std::to_string(solver.solve(problem));
        display.solution(expr);

        if(display.defineVar) {
          display.defineVar = !display.defineVar;
          std::cout << "\nDEFINE: " << "FALSE\n";
        }
      } catch (int errorCode) {
        display.readyToSolve = false;
        cout << "Error #: " + std::to_string(errorCode);
        display.solution("Error: " + std::to_string(errorCode));
      }
      display.readyToSolve=false;
    }

    BeginDrawing();
    ClearBackground(WHITE);

    display.draw();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
