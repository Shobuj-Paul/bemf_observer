#pragma once

#include <math/foc.hpp>
#include <controllers/pi_controller.hpp>

namespace observers
{
struct bemf_gains
{
  float VOLTAGE_GAIN, CURRENT_GAIN, EMF_GAIN, SPEED_CURRENT_GAIN;
};

class bemf_solver
{
  float angular_velocity, rotor_angle, Ts;
  math::frame_dq I, V, X, E, I_prev, X_prev;
  const bemf_gains& gains;
  controllers::pi_config update_config;
  controllers::pi_controller d_axis, q_axis;

public:
  bemf_solver(const controllers::pi_config& config, const bemf_gains& gains, float Ts);
  float loop(math::frame_abc line_currents, math::frame_abc line_voltages, float angular_velocity, float rotor_angle);
};
}  // namespace observers
