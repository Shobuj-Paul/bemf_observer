#include <iostream>
#include <math/foc.hpp>
#include <observers/bemf_observer.hpp>
#include <observers/dq_update.hpp>
#include <observers/tracker.hpp>
#include <controllers/pi_controller.hpp>
#define Ts 1e-4

int main()
{
  uint8_t idle_mode = 0;
  bool force_bemf = false, en_dis_6_step_comm = false;
  float angle = 0, Vbus = 12;

  math::FrameABC line_currents, line_voltages;
  math::FrameDQ U;

  observers::BemfGains gains(1, 1, 1, Ts, 0);
  observers::BemfObserver bemf_observer(Ts, 16);

  observers::SetBemfParams set_bemf_params;
  observers::SetTrackerParams set_tracker_params;
  observers::ExtBemfParams ext_bemf_params;
  observers::ExtTrackerParams ext_tracker_params;

  for (float t = 0; t < 10; t += Ts)
  {
    math::FrameABC duties = math::inverse_clarke_transform(math::inverse_park_transform(U, angle));
    observers::BemfOutput output =
        bemf_observer.loop(line_currents, line_voltages, duties, Vbus, set_bemf_params, set_tracker_params,
                           ext_bemf_params, ext_tracker_params, idle_mode, force_bemf, en_dis_6_step_comm);
    angle = output.e_theta_deg;
    std::cout << "Duties: " << duties.a << " " << duties.b << " " << duties.c << std::endl;
  }
}
