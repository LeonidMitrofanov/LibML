#pragma once

#include "../core.hpp"

template <typename targets_t> class IModel {
public:
  virtual ~IModel() = default;
  virtual void fit(const types::samples &X, const types::classification_targets &y) = 0;
  virtual types::classification_targets predict(const types::samples &X) const = 0;
};
