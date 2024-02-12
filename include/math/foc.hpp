#pragma once

namespace math
{
struct frame_abc
{
  float a, b, c;
  frame_abc() = default;
  frame_abc(float a, float b, float c) : a(a), b(b), c(c)
  {
  }
};

struct frame_alpha_beta
{
  float alpha, beta;
  frame_alpha_beta() = default;
  frame_alpha_beta(float alpha, float beta) : alpha(alpha), beta(beta)
  {
  }
};

struct frame_dq
{
  float d, q;
  frame_dq() = default;
  frame_dq(float d, float q) : d(d), q(q)
  {
  }
};

frame_alpha_beta clarke_transform(frame_abc X);
frame_dq park_transform(frame_alpha_beta X, float angle);

}  // namespace math
