#pragma once

#include <memory>
#include <math/foc.hpp>
#include <controllers/pi_controller.hpp>

namespace observers
{

struct SetBemfParams
{
  bool error_d, error_sum_d, id_est, error_q, error_sum_q, iq_est;
  SetBemfParams() : error_d(false), error_sum_d(false), id_est(false), error_q(false), error_sum_q(false), iq_est(false)
  {
  }
  SetBemfParams(bool error_d, bool error_sum_d, bool id_est, bool error_q, bool error_sum_q, bool iq_est)
    : error_d(error_d)
    , error_sum_d(error_sum_d)
    , id_est(id_est)
    , error_q(error_q)
    , error_sum_q(error_sum_q)
    , iq_est(iq_est)
  {
  }
};

struct ExtBemfParams
{
  float error_d, error_sum_d, id_est, error_q, error_sum_q, iq_est;
  ExtBemfParams() : error_d(0), error_sum_d(0), id_est(0), error_q(0), error_sum_q(0), iq_est(0)
  {
  }
  ExtBemfParams(float error_d, float error_sum_d, float id_est, float error_q, float error_sum_q, float iq_est)
    : error_d(error_d)
    , error_sum_d(error_sum_d)
    , id_est(id_est)
    , error_q(error_q)
    , error_sum_q(error_sum_q)
    , iq_est(iq_est)
  {
  }
};

struct BemfGains
{
  float VOLTAGE_GAIN, CURRENT_GAIN, EMF_GAIN, SPEED_CURRENT_GAIN;
  BemfGains(float Ld, float Lq, float Rs, float Ts, bool axis)
  {
    if (axis == 0)
    {
      VOLTAGE_GAIN = Ts / (2 * Ld + Rs * Ts);
      CURRENT_GAIN = Lq * Ts / (2 * Ld + Rs * Ts);
      EMF_GAIN = Ts / (2 * Ld + Rs * Ts);
      SPEED_CURRENT_GAIN = (2 * Ld - Rs * Ts) / (2 * Ld + Rs * Ts);
    }
    else if (axis == 1)
    {
      VOLTAGE_GAIN = Ts / (2 * Lq + Rs * Ts);
      CURRENT_GAIN = -Ld * Ts / (2 * Lq + Rs * Ts);
      EMF_GAIN = Ts / (2 * Lq + Rs * Ts);
      SPEED_CURRENT_GAIN = (2 * Lq - Rs * Ts) / (2 * Lq + Rs * Ts);
    }
  }
  BemfGains() : VOLTAGE_GAIN(0), CURRENT_GAIN(0), EMF_GAIN(0), SPEED_CURRENT_GAIN(0)
  {
  }
};

class DQUpdate
{
  math::FrameDQ I_prev, X_prev, E;
  std::unique_ptr<controllers::PIController> d_axis, q_axis;

public:
  controllers::PIConfig config;
  BemfGains gains;

  DQUpdate();
  DQUpdate(controllers::PIConfig config, BemfGains gains);
  float loop(math::FrameAlphaBeta currents, math::FrameAlphaBeta voltages, float angular_velocity, float rotor_angle,
             const SetBemfParams& set_params = SetBemfParams(), const ExtBemfParams& ext_params = ExtBemfParams());
  math::FrameDQ get_emfs() const;
};
}  // namespace observers
