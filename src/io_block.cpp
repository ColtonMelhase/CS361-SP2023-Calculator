#include "button.h"
#include "include/raylib.h"

class IoBlock {
public:
  Button input;
  Button output;

  IoBlock(Rectangle = {0, 0, 0, 0});
  IoBlock(Vector2, Vector2);
  IoBlock(float, float, float, float);

  void setRect(Rectangle);
  void setRect(Vector2, Vector2);
  void setRect(float, float, float, float);

  void draw();

private:
  Rectangle rect;
  bool updateRequired;

  void update();
};

IoBlock::IoBlock(Rectangle rectangle) : input(""), output("") {
  setRect(rectangle);
  input.center = false;
  output.center = false;
}

IoBlock::IoBlock(Vector2 position, Vector2 scale) : input(""), output("") {
  setRect(position, scale);
  input.center = false;
  output.center = false;
}

IoBlock::IoBlock(float x, float y, float width, float height)
    : input(""), output("") {
  setRect(x, y, width, height);
  input.center = false;
  output.center = false;
}

void IoBlock::setRect(Rectangle rectangle) {
  rect = rectangle;
  updateRequired = true;
}

void IoBlock::setRect(Vector2 position, Vector2 scale) {
  rect = {position.x, position.y, scale.x, scale.y};
  updateRequired = true;
}

void IoBlock::setRect(float x, float y, float width, float height) {
  rect = {x, y, width, height};
  updateRequired = true;
}

void IoBlock::draw() {
  update();

  input.draw();
  output.draw();
  DrawRectangleLinesEx(rect, 2, BLACK);
}

void IoBlock::update() {
  if (!updateRequired)
    return;

  updateRequired = false;

  input.setPostion(rect.x, rect.y, rect.width / 2, rect.height);
  output.setPostion(rect.x + rect.width / 2, rect.y, rect.width / 2,
                    rect.height);
}
