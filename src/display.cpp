#include "include/raylib.h"
#include "io_block.cpp"
#include "keypad.cpp"
#include <iostream>
#include <string>
#include <vector>

class Display {
public:
  std::string inputBuffer;
  std::string result;
  bool radians = false;
  bool inverseTrig = false;

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

  void processInput();
  std::string GetCharsPressed();
};

Display::Display() : keypad(0, 0, 0, 0) {
  Vector2 displaySize = {(float)GetScreenWidth(), (float)GetScreenHeight()};
  keypad.setRect(0, displaySize.y / 2, displaySize.x, displaySize.y / 2);
  history.push_back(IoBlock());

  int pos = 0;
  keypad.addButton("mode", pos);
  keypad.addButton("inv", pos);
  keypad.addButton("store", pos);

  pos++;
  keypad.addButton("d/dx", pos);
  keypad.addButton("pi", pos);
  keypad.addButton("e", pos);
  keypad.addButton("const", pos);

  pos++;
  keypad.addButton("sin", pos);
  keypad.addButton("cos", pos);
  keypad.addButton("tan", pos);

  pos++;
  keypad.addButton("varx", pos);
  keypad.addButton("^", pos);
  keypad.addButton("sqrt", pos);
  keypad.addButton("log", pos);
  keypad.addButton("ln", pos);

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
  keypad.addButton("hist", pos);
}

void Display::update() {
  displaySize = {(float)GetScreenWidth(), (float)GetScreenHeight()};
  keypad.setRect(0, displaySize.y / 2, displaySize.x, displaySize.y / 2);

  for (int i = 0; i < history.size(); i++) {
    history[i].setRect(0, displaySize.y / 2 - 24 * 2 * (history.size() - i),
                       displaySize.x, 24 * 2);
  }

  processInput();
}

void Display::draw() {
  for (int i = 0; i < history.size(); i++) {
    history[i].draw();
  }

  keypad.draw();
}

std::string Display::getProblem() {
  readyToSolve = false;

  for (int i = 0; i < history.size(); i++) {
    if (history[i].output.label == "") {
      return history[i].input.label;
    }
  }

  return history[0].output.label;
}

void Display::solution(std::string solution) {
  history.back().output.label = solution;
  history.push_back(IoBlock());
  readyToSolve = false;

  update();
}

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

  } else if (input == "const") {

  } else if (input == "varx") {

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
