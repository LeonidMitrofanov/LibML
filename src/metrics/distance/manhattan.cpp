#include "../../../include/metrics/distance.hpp"

types::distance manhattan(const types::sample &a, const types::sample &b) {
  types::distance sum = 0;
  for (size_t i = 0; i < a.size(); ++i) {
    sum += std::abs(a[i] - b[i]);
  }
  return sum;
}