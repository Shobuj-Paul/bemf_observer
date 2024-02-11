#pragma once

#include<controllers/pi_controller.hpp>
#include<math/operators.hpp>

namespace observers {
  class position_tracker {
    float speed_est, angle_est, Ts;
    controllers::pi_controller tracker;
    controllers::pi_config tracker_config;
    operators::integrator integrate;

    public:
    position_tracker(controllers::pi_config config, float Ts);
    float loop(float phase_error);
  };
}
