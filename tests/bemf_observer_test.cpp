#include <iostream>
#include <math/foc.hpp>
#include <observers/bemf_observer.hpp>
#include <observers/dq_update.hpp>
#include <observers/tracker.hpp>
#include <controllers/pi_controller.hpp>
#define Ts 1e-4

int main() 
{
  observers::BemfGains gains(1, 1, 1, Ts, 0);
  observers::BemfObserver bemf_observer;

  math::frame_abc line_currents;
  math::frame_abc line_voltages;
  math::frame_dq U;
  float angle = 0, Vbus = 12;
  observers::SetBemfParams set_bemf_params;
  observers::SetTrackerParams set_tracker_params;
  observers::ExtBemfParams ext_bemf_params;
  observers::ExtTrackerParams ext_tracker_params;
  uint8_t pos_obs_mode = 2, idle_mode = 0, opmode = 3, num_rotor_poles = 8, freq_mode = 2;
  bool force_bemf = false, en_dis_6_step_comm = false;

  for(float t = 0; t < 10; t += Ts)
  {
    math::frame_abc duties = math::inverse_clarke_transform(math::inverse_park_transform(U, angle));
    observers::BemfOutput output = bemf_observer.loop(line_currents, line_voltages, duties, Vbus, Ts, set_bemf_params, set_tracker_params, ext_bemf_params, ext_tracker_params, pos_obs_mode, idle_mode, opmode, num_rotor_poles, freq_mode, force_bemf, en_dis_6_step_comm);
    angle = output.e_theta_deg;
    std::cout << "Duties: " << duties.a << " " << duties.b << " " << duties.c << std::endl;
  }
}