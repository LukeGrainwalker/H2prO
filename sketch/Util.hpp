#ifndef UTIL_HPP
#define UTIL_HPP

class NormalizedVector {
public:
  float x, y, z;

  NormalizedVector(int16_t _x, int16_t _y, int16_t _z) {
    double length = sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2));
    x = _x / length;
    y = _y / length;
    z = _z / length;
  }

  double scalar_multiply(NormalizedVector* vec) {
    return acos(x * vec->x + y * vec->y + z * vec->z);
  }
};



#endif