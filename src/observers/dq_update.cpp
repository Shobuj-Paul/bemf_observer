#include <observers/dq_update.hpp>
#include <math/functions.hpp>

observers::BemfSolver::BemfSolver() : I_prev(0, 0), X_prev(0, 0), E(0, 0)
{
}

float observers::BemfSolver::loop(math::FrameAlphaBeta currents, math::FrameAlphaBeta voltages,
                                  const controllers::PIConfig& config, const BemfGains& gains, float angular_velocity,
                                  float rotor_angle, const SetBemfParams& set_params, const ExtBemfParams& ext_params)
{
  math::FrameDQ I_est, error, X;

  math::FrameDQ I = math::park_transform(currents, rotor_angle);
  math::FrameDQ V = math::park_transform(voltages, rotor_angle);

  X.d = gains.VOLTAGE_GAIN * V.d + gains.SPEED_CURRENT_GAIN * I.q * angular_velocity + gains.EMF_GAIN * E.d;
  X.q = gains.VOLTAGE_GAIN * V.q + gains.SPEED_CURRENT_GAIN * I.d * angular_velocity + gains.EMF_GAIN * E.q;

  I_est.d = X.d + X_prev.d + gains.CURRENT_GAIN * I_prev.d;
  I_est.q = X.q + X_prev.q + gains.CURRENT_GAIN * I_prev.q;

  if (set_params.id_est)
    I_est.d = ext_params.id_est;
  if (set_params.iq_est)
    I_est.q = ext_params.iq_est;

  error.d = I_est.d - I.d;
  error.q = I_est.q - I.q;

  if (set_params.error_d)
    error.d = ext_params.error_d;
  if (set_params.error_q)
    error.q = ext_params.error_q;

  E.d = q_axis.loop(error.d, config, set_params.error_sum_d, ext_params.error_sum_d);
  E.q = d_axis.loop(error.q, config, set_params.error_sum_q, ext_params.error_sum_q);

  X_prev = X;
  I_prev = I_est;

  return math::atan2(E.d, E.q);
}

math::FrameDQ observers::BemfSolver::get_emfs() const
{
  return E;
}
