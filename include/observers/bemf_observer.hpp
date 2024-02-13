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
    bemf_observer(const bemf_gains& gains, const controllers::pi_config& update_config, const controllers::pi_config& tracker_config, float Ts);
    float loop(math::frame_abc line_currents, math::frame_abc line_voltages);
};
} // namespace observers
