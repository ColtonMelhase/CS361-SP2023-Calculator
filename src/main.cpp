#include <iostream>
#include "include/raylib.h"
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

const int screenWidth = 800;
const int screenHeight = 450;
Rectangle textDisplay = { screenWidth/2 - 100, 180, 225, 50 };

std::string GetCharsPressed() {
  std::string input;
  char character = GetCharPressed();
  while (character > 0) {
    input.push_back(character);
    character = GetCharPressed();
  }

  return input;
}

std::string GetPressedButton() {
  // !!!todo!!!
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    // for each button CheckCollisionPointRec(GetMousePosition(), Rect);
    return "mouseDown";
  }
  return "";
}

bool GetInput(std::vector<std::string> &history) {
  std::string output = GetPressedButton();

  if (IsKeyPressed(KEY_ENTER) || output == "enter") {
    history.push_back("");
    return true;
  } else if (IsKeyPressed(KEY_BACKSPACE) || output == "delete") {
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

void DrawDisplay(std::vector<std::string> history, std::string answer = "") {
  DrawText(history.back().c_str(), (int)textDisplay.x+5, (int)textDisplay.y + 8, 40, BLACK);
  for (int i = 0; i < history.size() - 1; i++) {
    DrawText(history[i].c_str(), (int)textDisplay.x+5, 225 - 12 - 24 * (history.size() - i - 1),
             24, GRAY);
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

  while (!WindowShouldClose()) {

    GetInput(history);

    BeginDrawing();
    ClearBackground(WHITE);

    DrawText("Calculator", (int)textDisplay.x, (int)textDisplay.y - 40, 24, BLACK);
    DrawRectangleLines((int)textDisplay.x, (int)textDisplay.y, (int)textDisplay.width, (int)textDisplay.height, DARKGRAY);

    DrawDisplay(history);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
