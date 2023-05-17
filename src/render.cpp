#include "constants.h"
#include "include/raylib.h"
#include <iostream>
#include <iterator>
#include <math.h>
#include <string>
#include <vector>

void DrawDisplay(std::vector<std::string>, std::string = "");
void DrawButtons(Rectangle, std::vector<std::string>, int);
void DrawButton(std::string, Rectangle, Color = GRAY);

// Draws user input, errors, and solutions
void DrawDisplay(std::vector<std::string> history, std::string answer) {
  DrawText(history.back().c_str(), (int)textDisplay.x + 5,
           (int)textDisplay.y + 8, 40, BLACK);
  for (int i = 0; i < history.size() - 1; i++) {
    DrawText(history[i].c_str(), (int)textDisplay.x + 5,
             (int)textDisplay.y - 24 * (history.size() - i - 1), 24, GRAY);
  }
}

void DrawButtons(Rectangle rect, std::vector<std::string> buttons, int wrap) {
  Rectangle button;
  Vector2 dimentions = {rect.width / wrap,
                        rect.height / std::ceil((float)buttons.size() / wrap)};

  for (int i = 0; i < buttons.size(); i++) {
    if (buttons[i] == "")
      continue;

    button = {
        rect.x + (i % wrap) * dimentions.x,
        rect.y + (int)(i / wrap) * dimentions.y,
        dimentions.x,
        dimentions.y,
    };

    DrawButton(buttons[i], button);
  }

  DrawRectangleLinesEx(rect, 5, BLACK);
}

// Draws a square button with centered text
void DrawButton(std::string name, Rectangle rect, Color bg_color) {

  int fontSize = 24;
  int textOffset = MeasureText(name.c_str(), fontSize) / 2;
  bool hover = CheckCollisionPointRec(GetMousePosition(), rect);

  Vector2 offset = {rect.x + rect.width / 2 - textOffset,
                    rect.y + rect.height / 2 - (float)fontSize / 2};

  if (hover) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      bg_color = ColorBrightness(bg_color, -.5);
    }
  }

  DrawRectangleRec(rect, bg_color);
  DrawText(name.c_str(), offset.x, offset.y, fontSize, BLACK);

  if (hover) {
    DrawRectangleLinesEx(rect, 5, BLACK);
  }
}
