#include<observers/tracker.hpp>

observers::position_tracker::position_tracker(controllers::pi_config config, float Ts) : speed_est(0), angle_est(0), tracker_config(config), Ts(Ts) {}

float observers::position_tracker::loop(float phase_error) {
  speed_est += Ts*tracker.loop(phase_error, tracker_config);
  angle_est = operators::wrap_angle(integrate.loop(speed_est, Ts));
}