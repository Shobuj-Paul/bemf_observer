#pragma once

#include <math/foc.hpp>
#include <controllers/pi_controller.hpp>

namespace observers
{
struct bemf_gains
{
  float VOLTAGE_GAIN, CURRENT_GAIN, EMF_GAIN, SPEED_CURRENT_GAIN;
  bemf_gains(float Ld, float Lq, float Rs, float Ts, int axis)
  {
    if(axis == 0) {
      VOLTAGE_GAIN = Ts/(2*Ld + Rs*Ts);
      CURRENT_GAIN = Lq*Ts/(2*Ld + Rs*Ts);
      EMF_GAIN = Ts/(2*Ld + Rs*Ts);
      SPEED_CURRENT_GAIN = (2*Ld - Rs*Ts)/(2*Ld + Rs*Ts);
    }
    if(axis == 1) {
      VOLTAGE_GAIN = Ts/(2*Lq + Rs*Ts);
      CURRENT_GAIN = -Ld*Ts/(2*Lq + Rs*Ts);
      EMF_GAIN = Ts/(2*Lq + Rs*Ts);
      SPEED_CURRENT_GAIN = (2*Lq - Rs*Ts)/(2*Lq + Rs*Ts);
    }
  }
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
