#include <iostream>
#include <cmath>
#include <math/functions.hpp>
#include <math/cordic.hpp>

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <angle>" << std::endl;
    return 1;
  }
  int angle = atoi(argv[1]);
  int angle_cordic = (angle << 16) / 360;
  CORDIC::Trig trig = CORDIC::trig(angle_cordic);
  std::cout << "sin(x) in cru = " << trig.sin << " "
            << "cos(x) in cru = " << trig.cos << std::endl;
  float sine = (float)trig.sin / 16384.0F;
  float cosine = (float)trig.cos / 16384.0F;
  std::cout << "std::sin(x) error = " << std::sin(angle * PI / 180) - sine << " "
            << "std::cos(x) error = " << std::cos(angle * PI / 180) - cosine << std::endl;
  std::cout << "math::sin(x) error = " << math::sin(angle * PI / 180) - sine << " "
            << "math::cos(x) error = " << math::cos(angle * PI / 180) - cosine << std::endl;
  return 0;
}
