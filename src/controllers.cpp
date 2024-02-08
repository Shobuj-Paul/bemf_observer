#include <controllers.hpp>

pi_controller::pi_controller() : error_sum(0), output(0), error_prev(0) {}

float pi_controller::clamp(float input, float upper_limit, float lower_limit) {
  if(input < lower_limit)
    return lower_limit;
  else if(input > upper_limit)
    return upper_limit;
  else
    return input;
}    

float pi_controller::loop(float error, const pi_config& config) {

  if(error > 0 && output >= config.upper_limit)
    error = 0;
  else if(error < 0 && output <= config.lower_limit)
    error = 0;
  
  error_sum += clamp(config.Ki*config.Ts*(error + error_prev)/2, config.upper_limit, config.lower_limit); 
  output = clamp(config.Kp*error + config.Ki*error_sum, config.upper_limit, config.lower_limit);

  error_prev = error;

  return output;
}
