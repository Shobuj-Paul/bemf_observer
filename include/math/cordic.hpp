#pragma once

#include <cstdint>

namespace CORDIC
{
struct Trig
{
  int cos, sin;
};
Trig trig(int32_t angle);
}  // namespace CORDIC
