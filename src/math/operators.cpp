#include <math/operators.hpp>

operators::differentiator::differentiator() : input_prev(0) {}

float operators::differentiator::loop(float input, float Ts) {
  output = (input - input_prev)/Ts;
}

operators::integrator::integrator() : output(0), input_prev(0) {}

float operators::integrator::loop(float input, float Ts) {
  output += Ts*(input + input_prev)/2;
}

float operators::wrap_angle(float input) {
  if(input < -PI)
    return input + PI;
  if(input > PI)
    return input - PI;
  else 
    return input;
}