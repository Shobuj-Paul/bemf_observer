#include <iostream>
#include <controllers/pi_controller.hpp>
#include <math/functions.hpp>
#define Ts 0.01

using namespace controllers;

int main()
{
  float x_meas = 0, x_ref = 10;
  PIConfig config = { 2, 1, Ts, 10, -10 };
  PIController controller;
  std::cout << " Starting loop" << std::endl;
  for (float t = 0; t < 10; t += Ts)
  {
    float error = x_ref - x_meas;
    if (math::abs(error) < 0.1 && t > 5)
      break;
    x_meas += Ts * controller.loop(error, config);
    std::cout << "t = " << t << " x = " << x_meas << std::endl;
  }
}
