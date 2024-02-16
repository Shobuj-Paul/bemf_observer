#include <observers/bemf_observer.hpp>

observers::BemfObserver::BemfObserver() : speed_prev(0), angle_prev(0)
{
}

observers::BemfOutput observers::BemfObserver::loop(math::frame_abc line_currents, math::frame_abc line_voltages, math::frame_abc duties, 
                float Vbus, const float Ts, const SetBemfParams& set_bemf_params, const SetTrackerParams& set_tracker_params, 
                const ExtBemfParams& ext_bemf_params, const ExtTrackerParams& ext_tracker_params, uint8_t pos_obs_mode, uint8_t idle_mode, 
                uint8_t opmode, const uint8_t num_rotor_poles, const uint8_t freq_mode, bool force_bemf, bool en_dis_6_step_comm)
{
  observers::BemfOutput output;

  math::frame_alpha_beta currents = math::clarke_transform(line_currents);
  math::frame_alpha_beta voltages;
  if(idle_mode)
    voltages = math::clarke_transform(line_voltages);
  else {
    // Vbus Filter
    Vbus = 0.01* Vbus + 0.99*Vbus_prev;
    Vbus_prev = Vbus;

    // Duty Correction
    math::frame_abc duty_corrected;
    float duty_average = (duties.a + duties.b + duties.c) / 3;
    duty_corrected.a = duties.a - duty_average;
    duty_corrected.b = duties.b - duty_average;
    duty_corrected.c = duties.c - duty_average;

    // Duty to Voltage
    voltages = math::clarke_transform(duty_corrected);
    voltages.alpha = voltages.alpha*Vbus;
    voltages.beta = voltages.beta*Vbus;

  }

  const observers::BemfGains bemf_gains(0.0001, 0.0001, 0.1, Ts, 0);
  const controllers::PIConfig update_config = [freq_mode, opmode, Ts](){
    controllers::PIConfig config = {0.1, 0.1, Ts, -180, 180};
    return config;
  }();
  const controllers::PIConfig track_config = [freq_mode, opmode, Ts](){
    controllers::PIConfig config = {0.1, 0.1, Ts, -180, 180};
    return config;
  }();

  float phase_error = dq_update.loop(currents, voltages, update_config, bemf_gains, speed_prev, angle_prev, set_bemf_params, ext_bemf_params);
  float angle = tracker.loop(phase_error, track_config, set_tracker_params, ext_tracker_params);
  float speed = tracker.speed_tracker(angle, Ts);

  // Process Tracker Output
  output.phase_error_rad = phase_error;
  output.m_speed_rpm_raw = speed * 30 / (PI * num_rotor_poles/2);
  float angular_velocity = [speed, set_tracker_params, ext_tracker_params, this]() -> float {
    constexpr float alpha = 0.01;
    if(set_tracker_params.speed)
      return set_tracker_params.speed;
    else
      return speed*alpha + (1-alpha)*speed_prev;
  }();
  output.m_speed_rpm = angular_velocity * 30 / (PI * num_rotor_poles/2);
  output.e_theta_deg = [angular_velocity, angle, Ts, this]() -> float {
    float e_theta_deg = (angular_velocity * Ts + angle) * 180/PI;
    if(e_theta_deg > 180)
      e_theta_deg -= 360;
    else if(e_theta_deg < -180)
      e_theta_deg += 360;
    if (angular_velocity < 0 && e_theta_deg > 0)
      e_theta_deg -= 180;
    else if (angular_velocity < 0 && e_theta_deg < 0)
      e_theta_deg += 180;
    return e_theta_deg;
  }();
  output.e_theta_deg_6_step = [angle, en_dis_6_step_comm]() -> float {
    float angle_deg = angle * 180 / PI;
    if(en_dis_6_step_comm)
    {
      if(angle_deg >= -150 && angle_deg < -90)
        return -120;
      else if(angle_deg >= -90 && angle_deg < -30)
        return -60;
      else if(angle_deg >= -30 && angle_deg < 30)
        return 0;
      else if(angle_deg >= 30 && angle_deg < 90)
        return 60;
      else if(angle_deg >= 90 && angle_deg < 150)
        return 120;
      else if(angle_deg >= 150 || angle_deg < -150)
        return 180;
      else
        return 0;
    }
    else
      return angle_deg;
  }();

  //Bemf Stablility SMD
  if(pos_obs_mode == 2) {

  }
  if(idle_mode) {

  }
  if(force_bemf) {

  }

  speed_prev = speed;
  angle_prev = angle;

  return output;
}