#include <observers/tracker.hpp>

int main()
{
  controllers::PIConfig config = { 0.5, 100, 1e-4, 180, -180 };
  auto tracker = observers::Tracker(config);
  float phase_error = 10;

  for (float t = 0; t < 10; t += 1e-4)
  {
    tracker.loop(phase_error);
  }
  return 0;
}
