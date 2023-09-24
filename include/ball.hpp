#ifndef BALL_HPP
#define BALL_HPP

#include <raylib.h>

namespace Game {
class Ball {
public:
  Vector2 position = {0, 0};
  Vector2 velocity = {0, 0};
  Color color = RED;
  float radius = 10;

  void gotoCenter();

  void draw();
  void update();

  void shoot(Vector2 force);
  void shoot(Vector2 direction, float force);
};
} // namespace Game

#endif
