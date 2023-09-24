#include "../include/ball.hpp"
#include <raymath.h>

void Game::Ball::draw() { DrawCircle(position.x, position.y, radius, color); }

void Game::Ball::gotoCenter() {
  position.x = static_cast<float>(GetScreenWidth()) / 2;
  position.y = static_cast<float>(GetScreenHeight()) / 2;
}

void Game::Ball::update() {
  // limit ball speed
  float speed = Vector2Length(velocity);
  if (speed > 8)
    velocity = Vector2Scale(velocity, 0.95f);
  else if (speed < 6)
    velocity = Vector2Scale(velocity, 1.1f);

  // update ball position based on velocity
  position.x += velocity.x;
  position.y += velocity.y;

  // collide with top wall
  if (position.y - radius < 0) {
    position.y = radius;
    velocity.y *= -1;
  }

  // collide with bottom wall
  if (position.y + radius > GetScreenHeight()) {
    position.y = GetScreenHeight() - radius;
    velocity.y *= -1;
  }
}

void Game::Ball::shoot(Vector2 force) {
  velocity.x += force.x;
  velocity.y += force.y;
}

void Game::Ball::shoot(Vector2 direction, float force) {
  direction = Vector2Normalize(direction);

  velocity.x += direction.x * force;
  velocity.y += direction.y * force;
}
