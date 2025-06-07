#include "../../../include/metrics/distance.hpp"

types::distance euclidean(const types::sample &a, const types::sample &b) {
  types::distance sum = 0;
  for (size_t i = 0; i < a.size(); ++i) {
    sum += (a[i] - b[i]) * (a[i] - b[i]);
  }
  return std::sqrt(sum);
}