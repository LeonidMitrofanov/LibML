#include "../../../include/metrics/classification.hpp"

types::proba recall(const types::classification_targets &y_true,
               const types::classification_targets &y_pred,
               const types::classification_target target_class) {
  if (y_true.size() != y_pred.size()) {
    throw std::invalid_argument("y_true and y_pred must have the same size");
  }
  size_t tp = 0;
  size_t fn = 0;

  for (size_t i = 0; i < y_true.size(); ++i) {
    if (y_true[i] == target_class && y_pred[i] == target_class) {
      ++tp;
    } else if (y_true[i] == target_class && y_pred[i] != target_class) {
      ++fn;
    }
  }

  return static_cast<types::proba>(tp) / (tp + fn);
}