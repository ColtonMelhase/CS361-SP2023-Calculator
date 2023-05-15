#include "include/raylib.h"
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

const int screenWidth = 800;
const int screenHeight = 450;
Rectangle textDisplay = {(float)screenWidth / 2 - 100, 180, 225, 50};

// Gets keyboboard input and returns a string
std::string GetCharsPressed() {
  std::string input;
  char character = GetCharPressed();
  while (character > 0) {
    input.push_back(character);
    character = GetCharPressed();
  }

  return input;
}

// Returns the name of the pressed GUI button
// or an empty string if no buttons were pressed
std::string GetPressedButton() {
  // !!!todo!!!
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    // for each button CheckCollisionPointRec(GetMousePosition(), Rect);
    return "mouseDown";
  }
  return "";
}

// adds input to history
// returns true when input is ready to be computed
bool GetInput(std::vector<std::string> &history) {
  // get input from gui buttons
  std::string output = GetPressedButton();

  // if enter has been pressed on the gui or keyboard
  // add new history entry and return true to alert the solver that
  // the input is ready
  if (IsKeyPressed(KEY_ENTER) || output == "enter") {
    history.push_back("");
    return true;
  }
  // if backspace is pressed
  else if (IsKeyPressed(KEY_BACKSPACE) || output == "delete") {
    if (history.back().size()) {
      history.back().pop_back();
    }
    return false;
  } else {
    output.append(GetCharsPressed());
    history.back().append(output);
    return false;
  }
}

// Draws user input, errors, and solutions
void DrawDisplay(std::vector<std::string> history, std::string answer = "") {
  DrawText(history.back().c_str(), (int)textDisplay.x + 5,
           (int)textDisplay.y + 8, 40, BLACK);
  for (int i = 0; i < history.size() - 1; i++) {
    DrawText(history[i].c_str(), (int)textDisplay.x + 5,
             (int)textDisplay.y - 24 * (history.size() - i - 1), 24, GRAY);
  }
}

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
