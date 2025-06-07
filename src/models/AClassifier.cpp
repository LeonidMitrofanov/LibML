#include "../../include/models/AClassifier.hpp"
#include <algorithm>

const types::unique_classes &AClassifier::get_classes() const { return classes_; }

types::unique_classes
AClassifier::extract_unique_classes(const types::classification_targets &targets) {
  return types::unique_classes(targets.begin(), targets.end());
}