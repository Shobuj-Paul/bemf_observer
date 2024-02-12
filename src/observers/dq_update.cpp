#include <observers/dq_update.hpp>
#include <math/functions.hpp>

  observers::bemf_solver::bemf_solver(const controllers::pi_config& config, const bemf_gains& gains, float Ts)
  : angular_velocity(0), rotor_angle(0), update_config(config), gains(gains), Ts(Ts), X_prev(0, 0), I_prev(0, 0), V(0, 0), E(0, 0)
  {
  }

  float observers::bemf_solver::loop(math::frame_abc line_currents, math::frame_abc line_voltages, float angular_velocity, float rotor_angle)
  {
    I = math::park_transform(math::clarke_transform(line_currents), rotor_angle);
    V = math::park_transform(math::clarke_transform(line_voltages), rotor_angle);

    E.d = q_axis.loop(I.d - I_prev.d, update_config);
    E.q = d_axis.loop(I.q - I_prev.q, update_config);

    X.d = gains.VOLTAGE_GAIN*V.d + gains.SPEED_CURRENT_GAIN*I.q*angular_velocity + gains.EMF_GAIN*E.d;
    X.q = gains.VOLTAGE_GAIN*V.q + gains.SPEED_CURRENT_GAIN*I.d*angular_velocity + gains.EMF_GAIN*E.q;

    I.d = X.d + X_prev.d + gains.CURRENT_GAIN*I_prev.d;
    I.q = X.q + X_prev.q + gains.CURRENT_GAIN*I_prev.q;

    X_prev = X;
    I_prev = I;

    return math::atan2(E.q, E.d);
  }
