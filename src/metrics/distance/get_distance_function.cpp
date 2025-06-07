#include "../../../include/metrics/distance.hpp"

distance_function_t get_distance_function(const std::string &metric_name) {
  if (metric_name == "euclidean") {
    return euclidean;
  } else if (metric_name == "manhattan") {
    return manhattan;
  }
  throw std::invalid_argument("Invalid distance metric: " + metric_name);
}