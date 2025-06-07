#pragma once

#include "../../metrics/distance.hpp"
#include "../AClassifier.hpp"
#include <queue>
#include <string>

class KNN_Classifier : public AClassifier {
public:
  KNN_Classifier(size_t k, const std::string &distance_metric);

  void fit(const types::samples &X, const types::classification_targets &y);
  types::classification_targets predict(const types::samples &X) const;
  types::samples_probas predict_proba(const types::samples &X) const;

private:
  size_t k;
  types::samples X_train;
  types::classification_targets y_train;
  types::unique_classes classes_;
  types::distance_function get_distance;

  std::priority_queue<std::pair<types::distance, types::classification_target>>
  _get_nearest_classes(const types::sample &sample) const;
};