#pragma once

namespace math
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
  integrator(float initial_value = 0);
  float loop(float input, float Ts);
};

}  // namespace math
