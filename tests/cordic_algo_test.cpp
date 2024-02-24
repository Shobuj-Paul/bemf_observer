#include <iostream>
#include <cmath>
#include <math/functions.hpp>
#include <math/cordic.hpp>

int main()
{
  for (int i = -180; i <= 180; i++)
  {
    int angle_cordic = (i << 16) / 360;
    CORDIC::Trig trig = CORDIC::trig(angle_cordic);
    float sine = static_cast<float>(trig.sin) / 16384.0F;
    float cosine = static_cast<float>(trig.cos) / 16384.0F;
    if (math::abs(math::sin(i * PI / 180) - sine) > 0.001 || math::abs(math::cos(i * PI / 180) - cosine) > 0.001)
    {
      std::cerr << "Error exceeded threshold at angle: " << i << std::endl;
      return 1;
    }
  }
  return 0;
}
