#pragma once
#define PI 3.1415

namespace operators
{
class differentiator
{
  float output, input_prev, Ts;

public:
  differentiator();
  float loop(float input, float Ts);
};

class integrator
{
  float output, input_prev, Ts;

public:
  integrator();
  float loop(float input, float Ts);
};

float wrap_angle(float input);
}  // namespace operators
