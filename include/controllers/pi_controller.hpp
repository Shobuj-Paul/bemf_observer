#pragma once

namespace controllers
{
struct pi_config
{
  float Kp, Ki, Ts, upper_limit, lower_limit;
};

class pi_controller
{
  float error_sum, output, error_prev;
  float reset(float input, float output, float upper_limit, float lower_limit);
  float clamp(float input, float upper_limit, float lower_limit);

public:
  pi_controller();
  float loop(float error, const pi_config& config);
};
}  // namespace controllers
