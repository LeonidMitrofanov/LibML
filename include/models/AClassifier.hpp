#pragma once

#include "IModel.hpp"

class AClassifier : public IModel<types::classification_targets> {
protected:
  types::unique_classes classes_;

public:
  virtual ~AClassifier() = default;
  virtual types::samples_probas predict_proba(const types::samples &X) const = 0;
  const types::unique_classes &get_classes() const;
  static types::unique_classes
  extract_unique_classes(const types::classification_targets &targets);
};