#include <observers/dq_update.hpp>

int main()
{
  observers::BemfGains gains(1, 1, 1, 1e-4, 0);
  controllers::PIConfig config = { 0.5, 100, 1e-4, 100, -100 };
  auto dq_update = observers::DQUpdate(config, gains);
  for (float t = 0; t < 10; t += 1e-4)
  {
    math::FrameAlphaBeta currents(0, 0);
    math::FrameAlphaBeta voltages(0, 0);
    float angular_velocity = 0;
    float rotor_angle = 0;
    dq_update.loop(currents, voltages, angular_velocity, rotor_angle);
  }
  return 0;
}
