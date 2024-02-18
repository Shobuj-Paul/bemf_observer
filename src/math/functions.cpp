#include <math/functions.hpp>

float math::abs(float input)
{
  if (input < 0)
    return -input;
  else
    return input;
}

float math::pow(float input, int power)
{
  float output = 1;
  for (int i = 0; i < power; i++)
    output = output * input;
  return output;
}

float math::wrapAngle(float input)
{
  if (input < -PI)
    return input + PI;
  if (input > PI)
    return input - PI;
  else
    return input;
}

float math::sin(float angle)
{
  if (angle > PI / 2)
    angle = PI - angle;
  else if (angle < -PI / 2)
    angle = -PI - angle;
  float pow_2 = angle * angle;
  float pow_3 = pow_2 * angle;
  float pow_5 = pow_3 * pow_2;
  float pow_7 = pow_5 * pow_2;
  return (angle - pow_3 * 0.1667 + pow_5 * 0.008333 - pow_7 * 0.0001984);
}

float math::cos(float angle)
{
  return sin(angle + PI / 2);
}

float math::atan(float input)
{
  float reciprocal_input = 1 / input;
  if (input > 1)
  {
    return PI / 2 - reciprocal_input / (0.28125 * pow(reciprocal_input, 2) + 1);
  }
  else if (input < -1)
  {
    return -PI / 2 - reciprocal_input / (0.28125 * pow(reciprocal_input, 2) + 1);
  }
  else
  {
    return reciprocal_input / (0.28125 * pow(reciprocal_input, 2) + 1);
  }
}

float math::atan2(float y, float x)
{
  if (x > 0)
    return atan(y / x);
  else if (x < 0 && y >= 0)
    return atan(y / x) + PI;
  else if (x < 0 && y < 0)
    return atan(y / x) - PI;
  else if (x == 0 && y > 0)
    return PI / 2;
  else if (x == 0 && y < 0)
    return -PI / 2;
  else
    return 0;
}
