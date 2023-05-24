#include "include/raylib.h"
#include <iostream>

class Button {
public:
  std::string label;
  Rectangle rect;

  Button(std::string buttonLabel, Vector2 positiion, Vector2 scale);
  Button(std::string buttonLabel, float x, float y, float width, float height);
  bool pressed();
  void draw();
  void setLabel(std::string);

private:
  bool halfPress = false; // a full press is a press and release
  int fontSize = 24;
  Vector2 textOffset;
  Color bgColor;
  Color textColor;
};

Button::Button(std::string buttonLabel, Vector2 positiion, Vector2 scale) {
  setLabel(buttonLabel);
  rect = {positiion.x, positiion.y, scale.x, scale.y};
}

Button::Button(std::string buttonLabel, float x, float y, float width,
               float height) {
  setLabel(buttonLabel);
  rect = {x, y, width, height};
}

bool Button::pressed() {
  bool mouseOver = CheckCollisionPointRec(GetMousePosition(), rect);
  bool pressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
  bool released = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

  // if button has been pressed down and released by the mouse
  // it has received a full press
  if (halfPress && mouseOver && released) {
    halfPress = false;
    return true;
  }

  if (!mouseOver && released) {
    halfPress = false;
  }

  if (mouseOver && pressed) {
    halfPress = true;
  }

  return false;
}

void Button::draw() {
  bool hover = CheckCollisionPointRec(GetMousePosition(), rect);

  if (hover) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      bgColor = ColorBrightness(bgColor, -.5);
    }
  }

  DrawRectangleRec(rect, bgColor);
  DrawText(label.c_str(), textOffset.x, textOffset.y, fontSize, textColor);
}

void Button::setLabel(std::string buttonLabel) {
  int horizontalOffset = MeasureText(label.c_str(), fontSize) / 2;

  textOffset = {rect.x + rect.width / 2 - horizontalOffset,
                rect.y + rect.height / 2 - (float)fontSize / 2};

  label = buttonLabel;
}
