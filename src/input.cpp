#include "constants.h"
#include "include/raylib.h"
#include <iostream>
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
