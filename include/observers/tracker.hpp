#pragma once

#include <controllers/pi_controller.hpp>
#include <math/operators.hpp>
#include <math/functions.hpp>

namespace observers
{
class position_tracker
{
  float speed_est, angle_est, Ts;
  controllers::pi_controller angle_controller;
  controllers::pi_config tracker_config;
  math::integrator angle_integrator;

public:
  position_tracker(controllers::pi_config config, float Ts);
  float loop(float phase_error);
  float speed_tracker(float angle_est);
};
}  // namespace observers
