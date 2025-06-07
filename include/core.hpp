#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <functional>

// #define ML_VERSION_MAJOR 0
// #define ML_VERSION_MINOR 0
// #define ML_VERSION_PATCH 0

namespace types{
    using sample = std::vector<double>;
    using samples = std::vector<sample>;

    using regression_target = double;
    using regression_targets = std::vector<regression_target>;

    using classification_target = size_t;
    using classification_targets = std::vector<classification_target>;
    using unique_classes = std::unordered_set<classification_target>;

    using proba = double;
    using sample_probas = std::unordered_map<classification_target, proba>;
    using samples_probas = std::vector<sample_probas>;

    using distance = double;
    using distance_function = std::function<distance(const sample &, const sample &)>;
}