#ifndef BUTTON_H
#define BUTTON_H

#include "include/raylib.h"
#include <iostream>

class Button {
public:
  std::string label;
  int fontSize = 24;
  bool center = true;

  Button(std::string);
  Button(std::string, Rectangle);
  Button(std::string, Vector2, Vector2);
  Button(std::string, float, float, float, float);
  bool pressed();
  void draw();
  void setLabel(std::string);
  void setPostion(Rectangle);
  void setPostion(Vector2, Vector2);
  void setPostion(float, float, float, float);

private:
  Rectangle rect;
  bool halfPress = false; // a full press is a press and release
  int textWidth;
  Vector2 textOffset;
  Color bgColor = GRAY;
  Color textColor = BLACK;

  void setTextOffset();
};

#endif
