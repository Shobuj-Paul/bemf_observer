#include <observers/tracker.hpp>

observers::position_tracker::position_tracker(controllers::PIConfig config, float Ts)
  : speed_est(0), angle_est(0), Ts(Ts), tracker_config(config)
{
}

float observers::position_tracker::loop(float phase_error, const SetTrackerParams& set_params, const ExtTrackerParams& ext_params)
{
  if(set_params.error)
    phase_error = ext_params.error;
  angle_est += Ts * angle_controller.loop(phase_error, tracker_config, set_params.speed, ext_params.speed);
  if(set_params.etheta)
    angle_est = ext_params.etheta;
  angle_est = math::wrapAngle(angle_est);
  return angle_est;
}

float observers::position_tracker::speed_tracker(float angle_est)
{
  speed_est = angle_integrator.loop(angle_est, Ts);
  return speed_est;
}
