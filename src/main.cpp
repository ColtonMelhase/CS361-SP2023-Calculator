#include <iostream>
#include <raylib.h>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

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
  DrawText(history.back().c_str(), 24, 225 - 12, 24, BLACK);
  for (int i = 0; i < history.size() - 1; i++) {
    DrawText(history[i].c_str(), 24, 225 - 12 - 24 * (history.size() - i - 1),
             24, GRAY);
  }
}

int main() {
  InitWindow(800, 450, "Calculator");
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

    DrawDisplay(history);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
