#include <math/cordic.hpp>
#include <iostream>
#include <iostream>

CORDIC::Trig CORDIC::trig(int32_t angle)
{
  int8_t quadAdj = 1;
  // Shift angle to be in range -90 to 90
  if (angle > 16384)
  {
    angle = angle - 32768;
    quadAdj = -1;
  }
  else if (angle < -16384)
  {
    angle = angle + 32768;
    quadAdj = -1;
  }
  int32_t atan2[14] = { 8192, 4836, 2555, 1297, 651, 325, 162, 81, 40, 20, 10, 5, 2, 1 };
  int32_t x = 9949, y = 0, theta = 0;
  for (int32_t i = 0; i < 14; i++)
  {
    int8_t sigma = (angle > theta) ? 1 : -1;
    theta = theta + sigma * atan2[i];
    int32_t nx = x - sigma * (y >> i);
    y = y + sigma * (x >> i);
    x = nx;
  }
  return { quadAdj * x, quadAdj * y };
}
