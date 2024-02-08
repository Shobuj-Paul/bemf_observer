#pragma once

struct pi_config
{
  float Kp, Ki, Ts, upper_limit, lower_limit;
};

struct pid_config
{
  float Kp, Ki, Kd, Ts, upper_limit, lower_limit;
};

class pi_controller {
  float error_sum, output, error_prev;
  public:
  pi_controller();
  float clamp(float input, float upper_limit, float lower_limit);
  float loop(float error, const pi_config& config);
};

class pid_controller {
  float error_sum, output, error_prev;
  public:
  pid_controller();
  float clamp(float input, float upper_limit, float lower_limit);
  float loop(float error, const pid_config& config);
};
