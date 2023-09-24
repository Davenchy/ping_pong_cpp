#include "../include/paddle.hpp"
#include <cmath>

float Game::Paddle::window_padding = 10;

void Game::Paddle::gotoCenter() {
  rect.y = static_cast<float>(GetScreenHeight()) / 2 - rect.height / 2;
}

void Game::Paddle::draw() { DrawRectangleRec(rect, color); }

void Game::Paddle::update() {
  // if velocity is too small set it to 0
  if (std::abs(velocity) < 0.01)
    velocity = 0;
  // if velocity is too big set it to maximum velocity
  if (std::abs(velocity) > max_velocity)
    velocity = velocity > 0 ? max_velocity : -max_velocity;

  // update the position of the paddle based on the velocity
  rect.y += velocity;
  // decrease the velocity over time, so the paddle stops after a while
  velocity *= drag;

  // limit the paddle to the screen edges
  if (rect.y < 0)
    rect.y = 0;
  if (rect.y > GetScreenHeight() - rect.height)
    rect.y = GetScreenHeight() - rect.height;
}

void Game::Paddle::moveUp() { velocity -= speed; }

void Game::Paddle::moveDown() { velocity += speed; }
