#include "include/raylib.h"
#include "io_block.cpp"
#include "keypad.cpp"
#include <iostream>
#include <string>
#include <vector>

class Display {
public:
  bool radians = true; // input is in radians by default

  // is true when the display has a problem ready to solve
  bool readyToSolve = false;

  Display();

  void update();
  void draw();
  std::string getProblem();
  void solution(std::string);

private:
  Keypad keypad;
  Vector2 displaySize;
  std::vector<IoBlock> history;
  bool inverseTrig = false;
  bool shape_mode = false;

  void processInput();
  std::string GetCharsPressed();
};

// sets up the display and currently adds the buttons to the display
// will likly need to add buttons elsewhere in the future for
// organization and so they can be swaped out live
Display::Display() : keypad(0, 0, 0, 0) {
  Vector2 displaySize = {(float)GetScreenWidth(), (float)GetScreenHeight()};
  keypad.setRect(0, displaySize.y / 2, displaySize.x, displaySize.y / 2);
  history.push_back(IoBlock());

  int pos = 0;
  keypad.addButton("mode", pos);
  keypad.addButton("inv", pos);
  keypad.addButton("store", pos);
  keypad.addButton("shapes", pos);

  pos++;
  keypad.addButton("shapes", pos);

  pos++;
  keypad.addButton("int(", pos);
  keypad.addButton("pi", pos);
  keypad.addButton("e", pos);

  pos++;
  keypad.addButton("squareArea(", pos);
  keypad.addButton("squarePerimeter", pos);

  keypad.addButton("rectangleArea(", pos);
  keypad.addButton("rectanglePerimeter(", pos);

  keypad.addButton("cubeSurfaceArea(", pos);
  keypad.addButton("cubeVolume(", pos);

  keypad.addButton("rectangularPrismSurfaceArea(", pos);
  keypad.addButton("rectangularPrismVolume(", pos);

  pos++;
  keypad.addButton("trapezoidArea(", pos);
  keypad.addButton("trapezoidPerimeter(", pos);

  keypad.addButton("circleArea(", pos);
  keypad.addButton("circleCircumference(", pos);

  keypad.addButton("sphereSurfaceArea(", pos);
  keypad.addButton("sphereVolume(", pos);

  keypad.addButton("pyramidSurfaceArea(", pos);
  keypad.addButton("pyramidVolume(", pos);

  pos++;
  keypad.addButton("sin(", pos);
  keypad.addButton("cos(", pos);
  keypad.addButton("tan(", pos);

  pos++;
  keypad.addButton("asin(", pos);
  keypad.addButton("acos(", pos);
  keypad.addButton("atan(", pos);

  pos++;
  keypad.addButton("varx", pos);
  keypad.addButton("^", pos);
  keypad.addButton("^(0.5)", pos);
  keypad.addButton("log(", pos);
  keypad.addButton("ln(", pos);

  pos++;
  keypad.addButton("(", pos);
  keypad.addButton("1", pos);
  keypad.addButton("4", pos);
  keypad.addButton("7", pos);
  keypad.addButton("0", pos);

  pos++;
  keypad.addButton(")", pos);
  keypad.addButton("2", pos);
  keypad.addButton("5", pos);
  keypad.addButton("8", pos);
  keypad.addButton(".", pos);

  pos++;
  keypad.addButton("del", pos);
  keypad.addButton("3", pos);
  keypad.addButton("6", pos);
  keypad.addButton("9", pos);
  keypad.addButton("=", pos);

  pos++;
  keypad.addButton("clear", pos);
  keypad.addButton("+", pos);
  keypad.addButton("-", pos);
  keypad.addButton("*", pos);
  keypad.addButton("/", pos);
  keypad.addButton(",", pos);

  // hide buttons
  keypad.mask = {0, 2, 5, 7, 8, 9, 10, 11};
}

// updates UI elements and proccesses user input
void Display::update() {
  if (shape_mode) {
    keypad.mask = {1, 3, 4};
  } else {
    if (!inverseTrig) {
      keypad.mask = {0, 2, 5, 7, 8, 9, 10, 11};
    } else {
      keypad.mask = {0, 2, 6, 7, 8, 9, 10, 11};
    }
  }

  displaySize = {(float)GetScreenWidth(), (float)GetScreenHeight()};
  keypad.setRect(0, displaySize.y / 2, displaySize.x, displaySize.y / 2);

  for (int i = 0; i < history.size(); i++) {
    history[i].setRect(0, displaySize.y / 2 - 24 * 2 * (history.size() - i),
                       displaySize.x, 24 * 2);
  }

  processInput();
}

// Draws the display including keypad and input/output
void Display::draw() {
  for (int i = 0; i < history.size(); i++) {
    history[i].draw();
  }

  keypad.draw();
}

// gets current problem from the ui will return the same answer until solution
// is called or the problem is updated
std::string Display::getProblem() {
  for (int i = 0; i < history.size(); i++) {
    if (history[i].output.label == "") {
      return history[i].input.label;
    }
  }

  return history[0].output.label;
}

// updates the display to show the result of the problem and
// prepares for new input
void Display::solution(std::string solution) {
  history.back().output.label = solution;
  history.push_back(IoBlock());
  readyToSolve = false;

  update();
}

// process all input from the display and update the current display input
void Display::processInput() {
  std::string input = keypad.getKepadInput();
  input.append(GetCharsPressed());

  for (int i = 0; i < history.size(); i++) {
    if (history[i].input.pressed()) {
      history.back().input.label.append(history[i].input.label);
    } else if (history[i].output.pressed()) {
      history.back().input.label.append(history[i].output.label);
    }
  }

  // test for special input e.g. delete, clear, and radians
  if (IsKeyPressed(KEY_BACKSPACE) || input == "del") {
    if (history.back().input.label.empty())
      return;
    history.back().input.label.pop_back();

  } else if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_EQUAL) ||
             input == "=") {
    readyToSolve = true;

  } else if (input == "clear") {
    history.back().input.label.clear();

  } else if (input == "mode") {
    radians = !radians;

  } else if (input == "inv") {
    inverseTrig = !inverseTrig;

  } else if (input == "store") {
    std::cout << "Store not implemetned" << std::endl;

  } else if (input == "shapes") {
    shape_mode = !shape_mode;

  } else if (input == "varx") {

  } else if (input == "hist") {

  } else {
    history.back().input.label.append(input);
  }
}

// Gets keyboboard input and returns a string
std::string Display::GetCharsPressed() {
  std::string input;
  char character = GetCharPressed();
  while (character > 0) {
    input.push_back(character);
    character = GetCharPressed();
  }

  return input;
}
