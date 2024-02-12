#include <math/functions.hpp>

float math::pow(float input, int power)
{
  float output = 1;
  for(int i=0; i<power; i++)
    output = output*input;
  return output;
}

float math::wrap_angle(float input)
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
  if(angle > PI/2)
    angle = PI - angle;
  else if(angle < -PI/2)
    angle = - PI - angle;
  else
    angle = angle;
  return (angle - pow(angle, 3)/6 + pow(angle, 5)/120 - pow(angle, 7)/5040);
}

float math::cos(float angle)
{
  return sin(angle + PI/2);
}
