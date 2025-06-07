#pragma once

#include "../core.hpp"
#include <string>

using distance_function_t = types::distance (*)(const types::sample &, const types::sample &);

distance_function_t get_distance_function(const std::string &metric_name);
types::distance euclidean(const types::sample &a, const types::sample &b);
types::distance manhattan(const types::sample &a, const types::sample &b);