#include "constants.h"
#include "include/raylib.h"
#include <iostream>
#include <math.h>
#include <vector>

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
std::string GetPressedButton(Rectangle rect, std::vector<std::string> buttons,
                             int wrap) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    // for each button CheckCollisionPointRec(GetMousePosition(), Rect);
    Rectangle button;
    Vector2 dimentions = {rect.width / wrap,
                          rect.height /
                              std::ceil((float)buttons.size() / wrap)};

    for (int i = 0; i < buttons.size(); i++) {
      if (buttons[i] == "")
        continue;

      button = {
          rect.x + (i % wrap) * dimentions.x,
          rect.y + (int)(i / wrap) * dimentions.y,
          dimentions.x,
          dimentions.y,
      };

      if (CheckCollisionPointRec(GetMousePosition(), button)) {
        return buttons[i];
      }
    }
  }
  return "";
}

// adds input to history
// returns true when input is ready to be computed
bool GetInput(std::vector<std::string> &history, Rectangle rect,
              std::vector<std::string> buttons, int wrap) {
  // get input from gui buttons
  std::string output = GetPressedButton(rect, buttons, wrap);

  // if enter has been pressed on the gui or keyboard
  // add new history entry and return true to alert the solver that
  // the input is ready
  if (IsKeyPressed(KEY_ENTER) || output == "enter" || output == "=") {
    history.push_back("");
    return true;
  }
  // if backspace is pressed
  else if (IsKeyPressed(KEY_BACKSPACE) || output == "del") {
    if (history.back().size()) {
      history.back().pop_back();
    }
    return false;
  }
  // if clear is pressed
  else if (output == "clear") {
    history.back().clear();
    return false;
  } else {
    output.append(GetCharsPressed());
    history.back().append(output);
    return false;
  }
  
}
