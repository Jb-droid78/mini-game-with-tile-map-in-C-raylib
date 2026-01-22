#ifndef CLAMP_H
#define CLAMP_H

static inline float clamp(float v, float min, float max) 
{
  if (v < min) return min;
  if (v > max) return max;
  return v;
}

#endif // CLAMP_H
