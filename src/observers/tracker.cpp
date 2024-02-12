#include <observers/tracker.hpp>

observers::position_tracker::position_tracker(controllers::pi_config config, float Ts)
  : speed_est(0), angle_est(0), tracker_config(config), Ts(Ts)
{
}

float observers::position_tracker::loop(float phase_error)
{
  angle_est += Ts * angle_controller.loop(phase_error, tracker_config);
  return math::wrap_angle(angle_est);
}

float observers::position_tracker::speed_tracker(float angle_est)
{
  return angle_integrator.loop(angle_est, Ts);
}
