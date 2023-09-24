#include "include/ball.hpp"
#include "include/game_manager.hpp"
#include "include/paddle.hpp"
#include <raylib.h>

void cpu_paddle(Game::Paddle &paddle, const Game::Ball &ball) {
  float diff = ball.position.y - paddle.rect.y - paddle.rect.height / 2;

  if (diff < 0)
    paddle.moveUp();
  else
    paddle.moveDown();
}

void human_paddle(Game::Paddle &paddle) {
  if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_K))
    paddle.moveUp();
  else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_J))
    paddle.moveDown();
}

int main() {
  Game::Ball ball;
  Game::Paddle p1, p2;
  Game::GameManager gm(ball, p2, p1);

  InitWindow(800, 500, "PingPongCpp");
  SetTargetFPS(60);

  ball.gotoCenter();
  ball.shoot({1, -1}, 6);

  p1.rect.x = GetScreenWidth() - p1.rect.width - Game::Paddle::window_padding;
  p1.gotoCenter();

  p2.rect.x = Game::Paddle::window_padding;
  p2.gotoCenter();

  while (!WindowShouldClose()) {
    ball.update();

    p1.update();
    cpu_paddle(p1, ball);

    p2.update();
    human_paddle(p2);

    gm.update();

    BeginDrawing();
    ClearBackground(BLACK);

    gm.draw();
    ball.draw();
    p1.draw();
    p2.draw();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
