#pragma once

#include <controllers/pi_controller.hpp>
#include <math/operators.hpp>
#include <math/functions.hpp>

namespace observers
{
struct SetTrackerParams
{
  bool error, speed, etheta;
  SetTrackerParams() : error(false), speed(false), etheta(false) {}
  SetTrackerParams(bool error, bool speed, bool etheta) : error(error), speed(speed), etheta(etheta) {}
};

struct ExtTrackerParams
{
  float error, speed, etheta;
  ExtTrackerParams() : error(0), speed(0), etheta(0) {}
  ExtTrackerParams(float error, float speed, float etheta) : error(error), speed(speed), etheta(etheta) {}
};

class position_tracker
{
  float speed_est, angle_est, Ts;
  controllers::PIController angle_controller;
  controllers::PIConfig tracker_config;
  math::integrator angle_integrator;

public:
  position_tracker(controllers::PIConfig config, float Ts);
  float loop(float phase_error, const SetTrackerParams& params = SetTrackerParams(), const ExtTrackerParams& ext_params = ExtTrackerParams());
  float speed_tracker(float angle_est);
};
}  // namespace observers
