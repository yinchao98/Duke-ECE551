#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
Vector2D::Vector2D():x(0), y(0) {}

Vector2D::Vector2D(double init_x, double init_y):x(init_x), y(init_y) {}

void Vector2D::initVector(double init_x, double init_y) {
  x = init_x;
  y = init_y;
}

double Vector2D::getMagnitude() const{
  return std::sqrt(pow(x, 2) + pow(y, 2));
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const{
  Vector2D ans;
  ans.x = x + rhs.x;
  ans.y = y + rhs.y;
  return ans;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs){
  x += rhs.x;
  y += rhs.y;
  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const{
  double ans;
  ans = x * rhs.x + y * rhs.y;
  return ans;
}

void Vector2D::print() const{
  printf("<%.2f, %.2f>", x, y);
}
