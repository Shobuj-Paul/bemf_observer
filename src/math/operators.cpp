#include <math/operators.hpp>

math::differentiator::differentiator() : input_prev(0)
{
}

float math::differentiator::loop(float input, float Ts)
{
  output = (input - input_prev) / Ts;
  input_prev = output;
  return output;
}

math::integrator::integrator(float initial_value) : output(0), input_prev(initial_value)
{
}

float math::integrator::loop(float input, float Ts)
{
  output += Ts * (input + input_prev) / 2;
  input_prev = output;
  return output;
}
