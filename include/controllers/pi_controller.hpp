#pragma once

namespace controllers
{
struct PIConfig
{
  float Kp, Ki, Ts, upper_limit, lower_limit;
};

class PIController
{
  float error_sum, output, error_prev;
  float reset(float input, float output, float upper_limit, float lower_limit);
  float clamp(float input, float upper_limit, float lower_limit);

public:
  PIController();
  float loop(float error, const PIConfig& config, float external_integral = 0, bool reset_integral = false);
};
}  // namespace controllers
