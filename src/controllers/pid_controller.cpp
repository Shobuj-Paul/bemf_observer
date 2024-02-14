#include <controllers/pid_controller.hpp>

controllers::pid_controller::pid_controller() : error_sum(0), output(0), error_prev(0)
{
}

float controllers::pid_controller::clamp(float input, float upper_limit, float lower_limit)
{
  if (input < lower_limit)
    return lower_limit;
  else if (input > upper_limit)
    return upper_limit;
  else
    return input;
}

float controllers::pid_controller::reset(float input, float output, float upper_limit, float lower_limit)
{
  if (input > 0 && output >= upper_limit)
    return 0;
  else if (input < 0 && output <= lower_limit)
    return 0;
  else
    return input;
}

float controllers::pid_controller::loop(float error, const pid_config& config, float external_integral, bool reset_integral)
{
  if (error > 0 && output >= config.upper_limit)
    error = 0;
  else if (error < 0 && output <= config.lower_limit)
    error = 0;

  error_sum += config.Ki * config.Ts * (error + error_prev) / 2;
  if (reset_integral)
    error_sum = external_integral;
  error_sum = clamp(error_sum, config.upper_limit, config.lower_limit);
  float derror = (error - error_prev) / config.Ts;
  output =
      clamp(config.Kp * error + config.Ki * error_sum + config.Kd * derror, config.upper_limit, config.lower_limit);

  error_prev = error;

  return output;
}
