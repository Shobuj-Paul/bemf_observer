#pragma once

#include <memory>
#include <math/operators.hpp>
#include <math/functions.hpp>
#include <controllers/pi_controller.hpp>

namespace observers
{
struct SetTrackerParams
{
  bool error, speed, etheta;
  SetTrackerParams() : error(false), speed(false), etheta(false)
  {
  }
  SetTrackerParams(bool error, bool speed, bool etheta) : error(error), speed(speed), etheta(etheta)
  {
  }
};

struct ExtTrackerParams
{
  float error, speed, etheta;
  ExtTrackerParams() : error(0), speed(0), etheta(0)
  {
  }
  ExtTrackerParams(float error, float speed, float etheta) : error(error), speed(speed), etheta(etheta)
  {
  }
};

class Tracker
{
  float speed_est, angle_est;
  std::unique_ptr<controllers::PIController> angle_controller;
  std::unique_ptr<math::integrator> angle_integrator;

public:
  controllers::PIConfig config;

  Tracker() = default;
  Tracker(controllers::PIConfig config);
  float loop(float phase_error, const SetTrackerParams& params = SetTrackerParams(),
             const ExtTrackerParams& ext_params = ExtTrackerParams());
  float speed_tracker(float angle_est, float Ts);
};
}  // namespace observers
