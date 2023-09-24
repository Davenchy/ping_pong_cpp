#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "ball.hpp"
#include "paddle.hpp"

namespace Game {

class GameManager {
  Ball &ball;
  const Paddle &human_paddle;
  const Paddle &cpu_paddle;

  void onBallPaddleCollision(const Paddle &paddle);

public:
  unsigned int human_score = 0;
  unsigned int cpu_score = 0;

  int font_size = 164;

  GameManager(Ball &ball, const Paddle &human_paddle, const Paddle &cpu_paddle)
      : ball(ball), human_paddle(human_paddle), cpu_paddle(cpu_paddle) {}

  void update();
  void draw();
};

} // namespace Game

#endif
