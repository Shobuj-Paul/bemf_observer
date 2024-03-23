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

math::FrameABC math::space_vector_modulation(math::FrameAlphaBeta U)
{
  math::FrameABC duty;

  float Z = U.beta * 0.5F - U.alpha * 0.8660254037844386F;
  float Y = U.alpha * 0.8660254037844386F + U.beta * 0.5F;
  float X = U.beta;

  // Sector 1
  if ((-Y <= 0.F) && (-Z > 0.F) && (X > 0.F))
  {
    float T1 = (Z - X + 1.F) / 2;
    float T2 = T1 + X;
    float T3 = T2 - Z;

    duty.a = T3;
    duty.b = T2;
    duty.c = T1;
  }
  // Sector 2
  else if ((-Y <= 0.F) && (-Z <= 0.F))
  {
    float T1 = (1.F - Y - Z) / 2;
    float T2 = T1 + Y;
    float T3 = T2 + Z;

    duty.a = T2;
    duty.b = T3;
    duty.c = T1;
  }
  // Sector 3
  else if ((-Y > 0.F) && (-Z <= 0.F) && (X > 0.F))
  {
    float T1 = (Y - X + 1.F) / 2;
    float T2 = T1 - Y;
    float T3 = T2 + X;

    duty.a = T1;
    duty.b = T3;
    duty.c = T2;
  }
  // Sector 4
  else if ((-Y > 0.F) && (-Z <= 0.F) && (X <= 0.F))
  {
    float T1 = (X - Z + 1.F) / 2;
    float T2 = T1 + Z;
    float T3 = T2 - X;

    duty.a = T1;
    duty.b = T2;
    duty.c = T3;
  }
  // Sector 5
  else if ((-Y > 0.F) && (-Z > 0.F))
  {
    float T1 = (Z + Y + 1.F) / 2;
    float T2 = T1 - Z;
    float T3 = T2 - Y;

    duty.a = T2;
    duty.b = T1;
    duty.c = T3;
  }
  // Sector 6
  else if ((-Y <= 0.F) && (-Z > 0.F) && (X <= 0.F))
  {
    float T1 = (X - Y + 1.F) / 2;
    float T2 = T1 - X;
    float T3 = T2 + Y;

    duty.a = T3;
    duty.b = T1;
    duty.c = T2;
  }
  // Default
  else
  {
    duty.a = 0.F;
    duty.b = 0.F;
    duty.c = 0.F;
  }

  // Saturation of Duty A
  if (duty.a > 1.F)
    duty.a = 1.F;
  else if (duty.a < 0.F)
    duty.a = 0.F;
  else
    duty.a = duty.a;

  // Saturation of Duty B
  if (duty.b > 1.F)
    duty.b = 1.F;
  else if (duty.b < 0.F)
    duty.b = 0.F;
  else
    duty.b = duty.b;

  // Saturation of Duty C
  if (duty.c > 1.F)
    duty.c = 1.F;
  else if (duty.c < 0.F)
    duty.c = 0.F;
  else
    duty.c = duty.c;

  return duty;
}
