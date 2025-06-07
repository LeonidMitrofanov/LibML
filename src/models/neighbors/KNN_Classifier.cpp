#include "../../../include/models/neighbors/KNN_Classifier.hpp"

KNN_Classifier::KNN_Classifier(size_t k, const std::string &distance_metric)
    : k(k), get_distance(get_distance_function(distance_metric)) {}

void KNN_Classifier::fit(const types::samples &X,
                         const types::classification_targets &y) {
  if (X.size() != y.size())
    throw std::invalid_argument("X and y must have the same size");
  else if (k > X.size())
    throw std::invalid_argument(
        "k is greater than the number of training samples");

  X_train = X;
  y_train = y;
  classes_ = extract_unique_classes(y);
}

types::samples_probas KNN_Classifier::predict_proba(const types::samples &X) const {
  if (X_train.empty()) {
    throw std::invalid_argument("Model not fitted");
  } else if (X[0].size() != X_train[0].size()) {
    throw std::invalid_argument(
        "X and X_train must have the same number of features");
  }

  types::samples_probas result(X.size());
  for (size_t i = 0; i < X.size(); ++i) {
    auto pq = _get_nearest_classes(X[i]);
    while (!pq.empty()) {
      result[i][pq.top().second] += 1.0 / k;
      pq.pop();
    }
  }

  return result;
}

std::priority_queue<std::pair<types::distance, types::classification_target>>
KNN_Classifier::_get_nearest_classes(const types::sample &sample) const {
  std::priority_queue<std::pair<types::distance, types::classification_target>> pq;

  for (size_t i = 0; i < k && i < X_train.size(); ++i) {
    types::distance distance = get_distance(sample, X_train[i]);
    pq.push(std::make_pair(distance, y_train[i]));
  }

  for (size_t i = k; i < X_train.size(); ++i) {
    types::distance distance = get_distance(sample, X_train[i]);
    if (distance < pq.top().first) {
      pq.pop();
      pq.push(std::make_pair(distance, y_train[i]));
    }
  }

  return pq;
}

  types::classification_targets KNN_Classifier::predict(const types::samples &X) const {
  types::samples_probas probas = predict_proba(X);
  types::classification_targets predictions(X.size());

  for (size_t i = 0; i < X.size(); ++i) {
    types::classification_target best_class = 0;
    types::proba best_proba = -1.0;

    for (const auto &[class_label, proba] : probas[i]) {
      if (proba > best_proba) {
        best_proba = proba;
        best_class = class_label;
      }
    }
    predictions[i] = best_class;
  }

  return predictions;
}