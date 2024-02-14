# pragma once

#include <observers/dq_update.hpp>
#include <observers/tracker.hpp>
#include <math/foc.hpp>

namespace observers
{
class bemf_observer
{
    bemf_solver dq_update;
    position_tracker tracker;
    float speed, angle, Ts;
  public:
    bemf_observer(const BemfGains& gains, const controllers::PIConfig& update_config, const controllers::PIConfig& tracker_config, float Ts);
    float loop(math::frame_abc line_currents, math::frame_abc line_voltages);
};
} // namespace observers
