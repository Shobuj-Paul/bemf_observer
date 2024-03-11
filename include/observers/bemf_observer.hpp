#pragma once

#include <observers/dq_update.hpp>
#include <observers/tracker.hpp>
#include <math/foc.hpp>
#include <cstdint>

namespace observers
{

class BemfObserver
{
  float speed_prev, angle_prev, Vbus_prev;
  float m_speed_rpm, m_speed_rpm_raw, phase_error_rad, e_theta_deg, e_theta_deg_6_step;
  uint8_t stability_smd_state, bemf_stable, bemf_stability_flag;
  const uint8_t num_rotor_poles;

public:
  std::unique_ptr<DQUpdate> dq_update;
  std::unique_ptr<Tracker> tracker;
  float Ts;

  BemfObserver(const float Ts = 0, const uint8_t num_rotor_poles = 0);
  float loop(const math::FrameABC& line_currents, const math::FrameABC& line_voltages,
                  const math::FrameABC& duties, float Vbus, const SetBemfParams& set_bemf_params,
                  const SetTrackerParams& set_tracker_params, const ExtBemfParams& ext_bemf_params,
                  const ExtTrackerParams& ext_tracker_params, const uint8_t idle_mode, const bool force_bemf,
                  const bool en_dis_6_step_comm);
  float get_m_speed_rpm() const;
  float get_m_speed_rpm_raw() const;
  float get_phase_error_rad() const;
  float get_e_theta_deg() const;
  float get_e_theta_deg_6_step() const;
  uint8_t get_stability_smd_state() const;
  uint8_t get_bemf_stable() const;
  uint8_t get_bemf_stability_flag() const;
};
}  // namespace observers
