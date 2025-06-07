#pragma once

#include "../core.hpp"

types::proba accuracy(const types::classification_targets &y_true,
                 const types::classification_targets &y_pred,
                 const types::classification_target target_class = 1);

types::proba precision(const types::classification_targets &y_true,
                  const types::classification_targets &y_pred,
                  const types::classification_target target_class = 1);

types::proba recall(const types::classification_targets &y_true,
               const types::classification_targets &y_pred,
               const types::classification_target target_class = 1);

types::proba f1_score(const types::classification_targets &y_true,
                 const types::classification_targets &y_pred,
                 const types::classification_target target_class = 1);