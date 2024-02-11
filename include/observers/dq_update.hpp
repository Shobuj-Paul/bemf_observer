#pragma once

namespace observers {
  struct bemf_config
  {
    float voltage_gain, speed_current_gain, emf_gain;
  };
  

  class bemf_solver {
    float Ts;
    public:
    bemf_solver(const bemf_config config, float Ts);
  };
}