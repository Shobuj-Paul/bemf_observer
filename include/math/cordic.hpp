#pragma once

#include <cstdint>

namespace CORDIC
{
  struct Trig
  {
    int sin;
    int cos;
  };
  Trig trig(int angle);
}
