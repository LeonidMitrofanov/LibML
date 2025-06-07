#pragma once

#include "../core.hpp"

template <typename targets_t> class IModel {
public:
  virtual ~IModel() = default;
  virtual void fit(const types::samples &X, const targets_t &y) = 0;
  virtual targets_t predict(const types::samples &X) const = 0;
};
