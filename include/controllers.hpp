#pragma once

struct pi_config
{
  float Kp, Ki, Ts, upper_limit, lower_limit;
};

class pi_controller {
  float error_sum, output, error_prev;
  public:
  pi_controller();
  float clamp(float input, float upper_limit, float lower_limit);
  float loop(float error, const pi_config& config);
};
