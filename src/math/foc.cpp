#include <math/foc.hpp>
#include <math/functions.hpp>

  math::frame_alpha_beta clarke_transform(math::frame_abc X)
  {
    math::frame_alpha_beta Y;
    Y.alpha = X.a;
    Y.beta = (X.b - X.c)*0.5773;
    return Y;
  }

  math::frame_dq park_transform(math::frame_alpha_beta X, float angle)
  {
    math::frame_dq Y;
    float cosine = math::cos(angle), sine = math::sin(angle);
    Y.d = X.alpha*cosine + X.beta*sine;
    Y.q = -X.alpha*sine + X.beta*cosine;
    return Y;
  }
