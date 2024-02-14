#pragma once

namespace controllers
{

struct pid_config
{
  float Kp, Ki, Kd, Ts, upper_limit, lower_limit;
};

class pid_controller
{
  float error_sum, output, error_prev;
  float reset(float input, float output, float upper_limit, float lower_limit);
  float clamp(float input, float upper_limit, float lower_limit);

public:
  pid_controller();
  float loop(float error, const pid_config& config, float external_integral = 0, bool reset_integral = false);
};
}  // namespace controllers
