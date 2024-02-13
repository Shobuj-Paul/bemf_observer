#include <math/foc.hpp>
#include <math/functions.hpp>

math::frame_alpha_beta math::clarke_transform(math::frame_abc X)
{
  math::frame_alpha_beta Y;
  Y.alpha = X.a;
  Y.beta = (X.b - X.c) * 0.5773;
  return Y;
}

math::frame_dq math::park_transform(math::frame_alpha_beta X, float angle)
{
  math::frame_dq Y;
  float cosine = math::cos(angle), sine = math::sin(angle);
  Y.d = X.alpha * cosine + X.beta * sine;
  Y.q = -X.alpha * sine + X.beta * cosine;
  return Y;
}

math::frame_abc math::inverse_clarke_transform(math::frame_alpha_beta X)
{
  math::frame_abc Y;
  Y.a = X.alpha;
  Y.b = -0.5 * X.alpha + 0.866 * X.beta;
  Y.c = -0.5 * X.alpha - 0.866 * X.beta;
  return Y;
}

math::frame_alpha_beta math::inverse_park_transform(math::frame_dq X, float angle)
{
  math::frame_alpha_beta Y;
  float cosine = math::cos(angle), sine = math::sin(angle);
  Y.alpha = X.d * cosine - X.q * sine;
  Y.beta = X.d * sine + X.q * cosine;
  return Y;
}
