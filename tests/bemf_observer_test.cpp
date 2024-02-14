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
  controllers::PIConfig update_config = {1, 1, Ts, 180, -180};
  controllers::PIConfig tracker_config  = {1, 1, Ts, 180,-180};
  observers::bemf_observer bemf_observer(gains, update_config, tracker_config, Ts);

  math::frame_abc line_currents;
  math::frame_abc line_voltages;
  math::frame_dq U;

  for(float t = 0; t < 10; t += Ts)
  {
    float angle = bemf_observer.loop(line_currents, line_voltages);
    math::frame_abc duties = math::inverse_clarke_transform(math::inverse_park_transform(U, angle));
    std::cout << "Duties: " << duties.a << " " << duties.b << " " << duties.c << std::endl;
  }
}