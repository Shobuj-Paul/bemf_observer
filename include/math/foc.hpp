#pragma once

namespace math
{
struct FrameABC
{
  float a, b, c;
  FrameABC() = default;
  FrameABC(float a, float b, float c) : a(a), b(b), c(c)
  {
  }
};

struct FrameAlphaBeta
{
  float alpha, beta;
  FrameAlphaBeta() = default;
  FrameAlphaBeta(float alpha, float beta) : alpha(alpha), beta(beta)
  {
  }
};

struct FrameDQ
{
  float d, q;
  FrameDQ() = default;
  FrameDQ(float d, float q) : d(d), q(q)
  {
  }
};

FrameAlphaBeta clarke_transform(FrameABC X);

FrameDQ park_transform(FrameAlphaBeta X, float angle);

FrameABC inverse_clarke_transform(FrameAlphaBeta X);

FrameAlphaBeta inverse_park_transform(FrameDQ X, float angle);

}  // namespace math
