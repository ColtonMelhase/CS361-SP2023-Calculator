#include "button.h"
#include "include/raylib.h"
#include <iostream>
#include <string>
#include <vector>

class Keypad {
public:
  std::vector<int> mask;
  std::vector<std::vector<Button>> buttons;

  Keypad(Rectangle);
  Keypad(Vector2, Vector2);
  Keypad(float, float, float, float);

  void setRect(Rectangle);
  void setRect(Vector2, Vector2);
  void setRect(float, float, float, float);
  void addButton(std::string, int);
  std::string getKepadInput();
  void draw();

private:
  Rectangle rect;
  bool updateRequired;

  void update();
};

Keypad::Keypad(Rectangle rectangle) { setRect(rectangle); }

Keypad::Keypad(Vector2 position, Vector2 scale) {
  setRect(position.x, position.y, scale.x, scale.y);
}

Keypad::Keypad(float x, float y, float width, float height) {
  setRect(x, y, width, height);
}

void Keypad::setRect(Rectangle rectangle) {
  rect = rectangle;
  updateRequired = true;
  update();
}

void Keypad::setRect(Vector2 position, Vector2 scale) {
  rect = {position.x, position.y, scale.x, scale.y};
  updateRequired = true;
  update();
}

void Keypad::setRect(float x, float y, float width, float height) {
  rect = {x, y, width, height};
  updateRequired = true;
  update();
}

void Keypad::addButton(std::string label, int x) {
  updateRequired = true;

  while (x >= buttons.size()) {
    buttons.push_back(std::vector<Button>());

    if (mask.size() > 0) {
      mask.push_back(mask.back() + 1);
    } else {
      mask.push_back(0);
    }
  }

  buttons[x].push_back(Button(label, 0, 0, 0, 0));
}

std::string Keypad::getKepadInput() {
  update();

  for (int x = 0; x < mask.size(); x++) {
    for (int y = 0; y < buttons[mask[x]].size(); y++) {
      if (buttons[mask[x]][y].pressed()) {
        return buttons[mask[x]][y].label;
      }
    }
  }

  return "";
}

void Keypad::draw() {
  update();

  for (int x = 0; x < mask.size(); x++) {
    for (int y = 0; y < buttons[mask[x]].size(); y++) {
      buttons[mask[x]][y].draw();
    }
  }

  DrawRectangleLinesEx(rect, 5, BLACK);
}

void Keypad::update() {
  if (!updateRequired)
    return;

  updateRequired = false;

  int horizontalCount = mask.size();
  for (int x = 0; x < horizontalCount; x++) {
    int verticleCount = buttons[mask[x]].size();
    for (int y = 0; y < verticleCount; y++) {
      buttons[mask[x]][y].setPostion(
          rect.x + rect.width * x / (float)horizontalCount,
          rect.y + rect.height * y / (float)verticleCount,
          rect.width / (float)horizontalCount,
          rect.height / (float)verticleCount);
    }
  }
}
