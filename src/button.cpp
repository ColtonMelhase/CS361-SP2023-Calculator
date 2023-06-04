#include "button.h"

Button::Button(std::string buttonLabel) {
  setLabel(buttonLabel);
  rect = {0, 0, 0, 0};
}

Button::Button(std::string buttonLabel, Rectangle rectangle) {
  setLabel(buttonLabel);
  rect = {rectangle.x, rectangle.y, rectangle.width, rectangle.height};
}

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
  Color local_bgColor = bgColor;

  if (hover) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      local_bgColor = ColorBrightness(bgColor, -.5);
    } else {
      local_bgColor = ColorBrightness(bgColor, .5);
    }
  }

  DrawRectangleRec(rect, local_bgColor);
  DrawText(label.c_str(), textOffset.x, textOffset.y, fontSize, textColor);
  DrawRectangleLinesEx(rect, 1, BLACK);
}

void Button::setLabel(std::string buttonLabel) {
  if (center) {
    textWidth = MeasureText(buttonLabel.c_str(), fontSize);
  } else {
    textWidth = 0;
  }

  setTextOffset();

  label = buttonLabel;
}

void Button::setPostion(Rectangle rectangle) {
  rect = {rectangle.x, rectangle.y, rectangle.width, rectangle.height};
  setTextOffset();
}

void Button::setPostion(Vector2 positiion, Vector2 scale) {
  rect = {positiion.x, positiion.y, scale.x, scale.y};
  setTextOffset();
}

void Button::setPostion(float x, float y, float width, float height) {
  rect = {x, y, width, height};
  setTextOffset();
}

void Button::setTextOffset() {
  textOffset = {rect.x + rect.width / 2 - (float)textWidth / 2,
                rect.y + rect.height / 2 - (float)fontSize / 2};
}
