#include <observers/dq_update.hpp>
#include <math/functions.hpp>

observers::bemf_solver::bemf_solver(const controllers::PIConfig& config, const BemfGains& gains, float Ts)
  : angular_velocity(0)
  , rotor_angle(0)
  , Ts(Ts)
  , V(0, 0)
  , E(0, 0)
  , I_prev(0, 0)
  , X_prev(0, 0)
  , gains(gains)
  , update_config(config)
{
}

float observers::bemf_solver::loop(math::frame_abc line_currents, math::frame_abc line_voltages, float angular_velocity,
                                   float rotor_angle, const SetBemfParams& set_params, const ExtBemfParams& ext_params)
{
  math::frame_dq I_est;
  math::frame_dq error;

  I = math::park_transform(math::clarke_transform(line_currents), rotor_angle);
  V = math::park_transform(math::clarke_transform(line_voltages), rotor_angle);

  X.d = gains.VOLTAGE_GAIN * V.d + gains.SPEED_CURRENT_GAIN * I.q * angular_velocity + gains.EMF_GAIN * E.d;
  X.q = gains.VOLTAGE_GAIN * V.q + gains.SPEED_CURRENT_GAIN * I.d * angular_velocity + gains.EMF_GAIN * E.q;

  I_est.d = X.d + X_prev.d + gains.CURRENT_GAIN * I_prev.d;
  I_est.q = X.q + X_prev.q + gains.CURRENT_GAIN * I_prev.q;

  if(set_params.id_est)
    I_est.d = ext_params.id_est;
  if(set_params.iq_est)
    I_est.q = ext_params.iq_est;

  error.d = I_est.d - I.d;
  error.q = I_est.q - I.q;

  if(set_params.error_d)
    error.d = ext_params.error_d;
  if(set_params.error_q)
    error.q = ext_params.error_q;

  E.d = q_axis.loop(error.d, update_config, set_params.error_sum_d, ext_params.error_sum_d);
  E.q = d_axis.loop(error.q, update_config, set_params.error_sum_q, ext_params.error_sum_q);

  X_prev = X;
  I_prev = I_est;

  return math::atan2(E.d, E.q);
}
