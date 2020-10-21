#include "circle.hpp"
#include <cmath>

#define PI 3.1415926535

Circle::Circle(Point p, const double r): center(p), radius(r) {}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double centerDis = center.distanceFrom(otherCircle.center);
  double r1 = radius;
  double r2 = otherCircle.radius;
  if (r1 == 0 || r2 == 0 || centerDis >= r1 + r2) {
    return 0;
  }
  if (r2 - r1 >= centerDis) {
    return PI*r1*r1;
  } else if (r1 - r2 >= centerDis){
      return PI*r2*r2;
  }
  double cosVal1 = (r1*r1 + centerDis*centerDis - r2*r2)/(2*r1*centerDis);
  double cosVal2 = (r2*r2 + centerDis*centerDis - r1*r1)/(2*r2*centerDis);
  double degree1 = 2 * acos(cosVal1);
  double degree2 = 2 * acos(cosVal2);
  double s1 = 0.5 * degree1 * r1 * r1;
  double s2 = 0.5 * degree2 * r2 * r2;
  double t = r1 * centerDis * sin(0.5 * degree1);
  return s1 + s2 - t;
}
