#include "../../../include/metrics/classification.hpp"

types::proba accuracy(const types::classification_targets &y_true,
                 const types::classification_targets &y_pred, 
                 const types::classification_target target_class) {
  if (y_true.size() != y_pred.size()) {
    throw std::invalid_argument("y_true and y_pred must have the same size");
  }

  size_t correct = 0;
  size_t total = y_true.size();

  for (size_t i = 0; i < total; ++i) {
    if (y_true[i] == y_pred[i]) {
      ++correct;
    }
  }

  return static_cast<types::proba>(correct) / total;
}