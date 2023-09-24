#include "../include/game_manager.hpp"
#include <cmath>
#include <raylib.h>
#include <raymath.h>

void Game::GameManager::draw() {
  const char *human_score_text = TextFormat("%u", human_score);
  const char *cpu_score_text = TextFormat("%u", cpu_score);

  int human_text_length = MeasureText(human_score_text, font_size);
  int cpu_text_length = MeasureText(cpu_score_text, font_size);
  int x_value = GetScreenWidth() / 4;
  int y_value = GetScreenHeight() / 2 - font_size / 2;

  DrawText(human_score_text, x_value - human_text_length / 2, y_value,
           font_size, RAYWHITE);

  DrawText(cpu_score_text, GetScreenWidth() - x_value - cpu_text_length / 2,
           y_value, font_size, RAYWHITE);

  DrawLine(x_value * 2, 0, x_value * 2, GetScreenHeight(), RAYWHITE);
  DrawCircleLines(x_value * 2, GetScreenHeight() / 2, 80, RAYWHITE);
}

void Game::GameManager::update() {
  // if ball hits left wall then score goal for CPU and reset ball
  if (ball.position.x + ball.radius <= 0) {
    ball.gotoCenter();
    ball.velocity = {0, 0};
    ball.shoot({1, 0}, 6);
    cpu_score++;
  }

  // if ball hits right wall then score goal for human and reset ball
  if (ball.position.x - ball.radius >= GetScreenWidth()) {
    ball.gotoCenter();
    ball.velocity = {0, 0};
    ball.shoot({-1, 0}, 6);
    human_score++;
  }

  if (IsKeyPressed(KEY_SPACE) && human_score > 0) {
    ball.gotoCenter();
    ball.velocity = {0, 0};
    ball.shoot({-1, 0}, 6);
    human_score--;
  }

  // change ball direction on collision with any paddle
  if (CheckCollisionCircleRec(ball.position, ball.radius, human_paddle.rect))
    onBallPaddleCollision(human_paddle);
  if (CheckCollisionCircleRec(ball.position, ball.radius, cpu_paddle.rect))
    onBallPaddleCollision(cpu_paddle);
}

void Game::GameManager::onBallPaddleCollision(const Paddle &paddle) {
  static float timeA = -1, timer = 0;
  float time;

  float paddle_speed_ratio = paddle.velocity / paddle.max_velocity;
  float ball_speed = Vector2Length(ball.velocity);
  float y_touch =
      (ball.position.y - paddle.rect.y) / paddle.rect.height * 2 - 1;
  Vector2 normal = Vector2Normalize(ball.velocity);

  normal.y = (y_touch + paddle_speed_ratio) / 2;
  normal.x *= -1;
  ball.velocity = Vector2Scale(normal, ball_speed);

  // fix ball stuck glitch
  time = GetTime();

  if (time - timeA < 0.05)
    timer += GetFrameTime();
  else
    timer = 0;

  if (timer > 2) {
    ball.gotoCenter();
    ball.velocity = {0, 0};
    ball.shoot({-1, 0}, 6);
    timer = 0;
    TraceLog(LOG_INFO, "Glitch Detected!!");
  }
  timeA = GetTime();
}
