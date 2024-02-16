#include <math/foc.hpp>
#include <math/functions.hpp>

math::FrameAlphaBeta math::clarke_transform(math::FrameABC X)
{
  math::FrameAlphaBeta Y;
  Y.alpha = X.a;
  Y.beta = (X.b - X.c) * 0.5773;
  return Y;
}

math::FrameDQ math::park_transform(math::FrameAlphaBeta X, float angle)
{
  math::FrameDQ Y;
  float cosine = math::cos(angle), sine = math::sin(angle);
  Y.d = X.alpha * cosine + X.beta * sine;
  Y.q = -X.alpha * sine + X.beta * cosine;
  return Y;
}

math::FrameABC math::inverse_clarke_transform(math::FrameAlphaBeta X)
{
  math::FrameABC Y;
  Y.a = X.alpha;
  Y.b = -0.5 * X.alpha + 0.866 * X.beta;
  Y.c = -0.5 * X.alpha - 0.866 * X.beta;
  return Y;
}

math::FrameAlphaBeta math::inverse_park_transform(math::FrameDQ X, float angle)
{
  math::FrameAlphaBeta Y;
  float cosine = math::cos(angle), sine = math::sin(angle);
  Y.alpha = X.d * cosine - X.q * sine;
  Y.beta = X.d * sine + X.q * cosine;
  return Y;
}
