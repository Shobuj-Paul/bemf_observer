#pragma once

#include <observers/dq_update.hpp>
#include <observers/tracker.hpp>
#include <math/foc.hpp>
#include <cstdint>

namespace observers
{
struct BemfOutput
{
  float m_speed_rpm, m_speed_rpm_raw, phase_error_rad, e_theta_deg, e_theta_deg_6_step;
  uint8_t stability_smd_state, bemf_stable, bemf_stability_flag;
};

class BemfObserver
{
  float speed_prev, angle_prev, Vbus_prev;

public:
  DQUpdate dq_update;
  Tracker tracker;
  float Ts;

  BemfObserver(const float Ts = 0);
  BemfOutput loop(const math::FrameABC& line_currents, const math::FrameABC& line_voltages,
                  const math::FrameABC& duties, float Vbus,
                  const SetBemfParams& set_bemf_params,
                  const SetTrackerParams& set_tracker_params,
                  const ExtBemfParams& ext_bemf_params,
                  const ExtTrackerParams& ext_tracker_params,
                  const uint8_t idle_mode, const uint8_t num_rotor_poles,
                  const bool force_bemf, const bool en_dis_6_step_comm);
};
}  // namespace observers
