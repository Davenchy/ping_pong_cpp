#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <raylib.h>

namespace Game {
class Paddle {
public:
  Rectangle rect = {0, 0, 15, 100};
  Color color = RAYWHITE;
  float speed = 2;
  float velocity = 0;
  float max_velocity = 5;
  float drag = 0.88;
  static float window_padding;

  void gotoCenter();

  void draw();
  void update();

  void moveUp();
  void moveDown();
};

} // namespace Game

#endif
