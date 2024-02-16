#include <observers/tracker.hpp>

float observers::Tracker::loop(float phase_error, controllers::PIConfig config, const SetTrackerParams& set_params,
                               const ExtTrackerParams& ext_params)
{
  if (set_params.error)
    phase_error = ext_params.error;
  angle_est += config.Ts * angle_controller.loop(phase_error, config, set_params.speed, ext_params.speed);
  if (set_params.etheta)
    angle_est = ext_params.etheta;
  angle_est = math::wrapAngle(angle_est);
  return angle_est;
}

float observers::Tracker::speed_tracker(float angle_est, float Ts)
{
  return angle_integrator.loop(angle_est, Ts);
}
