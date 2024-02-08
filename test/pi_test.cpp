#include<iostream>
#include<controllers.hpp>
#define Ts 0.01

int main(int argc, char* argv[])
{
  float x_meas = 0, x_ref = 100;
  pi_config config = {2, 1, Ts, 10, -10};
  pi_controller controller;
  std::cout << " Starting loop" <<std::endl;
  for(float t = 0; t<10; t+=Ts)
  {
    x_meas += Ts*controller.loop(x_ref - x_meas, config);
    std::cout << "t = " << t << " x = " << x_meas << std::endl;
  }
}