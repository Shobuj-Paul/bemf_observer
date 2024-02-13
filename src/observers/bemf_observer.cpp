#include <observers/bemf_observer.hpp>

observers::bemf_observer::bemf_observer(const bemf_gains& gains, const controllers::pi_config& update_config, const controllers::pi_config& tracker_config, float Ts)
  : dq_update(update_config, gains, Ts), tracker(tracker_config, Ts), Ts(Ts)
{
}

float observers::bemf_observer::loop(math::frame_abc line_currents, math::frame_abc line_voltages)
{
  float phase_error = dq_update.loop(line_currents, line_voltages, speed, angle);
  float angle_est = tracker.loop(phase_error);
  speed = tracker.speed_tracker(angle_est);
  angle = angle_est;
  return angle;
}