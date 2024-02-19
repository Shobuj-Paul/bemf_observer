#include <math/cordic.hpp>
#include <iostream>

CORDIC::Trig CORDIC::trig(int angle)
{
  int32_t atan2[14] = { 8192, 4836, 2555, 1297, 651, 325, 162, 81, 40, 20, 10, 5, 2, 1 };
  int32_t x = 9949, y = 0, theta = 0, sigma, nx;
  for (int32_t i = 0; i < 14; i++)
  {
    sigma = (theta < angle) ? 1 : -1;
    theta = theta + sigma * atan2[i];
    if (theta == angle) break;
    nx = x - sigma * (y >> i);
    y = y + sigma * (x >> i);
    x = nx;
  }
  return { y, x };
}
