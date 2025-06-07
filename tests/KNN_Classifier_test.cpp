#include "../include/models/neighbors/KNN_Classifier.hpp"
#include <cassert>
#include <iostream>

void test_fit() {
  std::cout << "Testing fit method..." << std::endl;

  // Test case 1: Basic fit
  types::samples samples = {{1, 2}, {3, 4}, {5, 6}};
  types::classification_targets targets = {0, 1, 0};
  KNN_Classifier knn(3, "manhattan");
  knn.fit(samples, targets);

  // Test case 2: Invalid input sizes
  try {
    types::samples invalid_samples = {{1, 2}, {3, 4}};
    types::classification_targets invalid_targets = {0, 1, 0, 1};
    knn.fit(invalid_samples, invalid_targets);
    assert(false && "Should have thrown exception for mismatched sizes");
  } catch (const std::invalid_argument &e) {
    // Expected exception
  }

  // Test case 3: k greater than samples
  try {
    KNN_Classifier invalid_knn(5, "manhattan");
    invalid_knn.fit(samples, targets);
    assert(false && "Should have thrown exception for k > samples");
  } catch (const std::invalid_argument &e) {
    // Expected exception
  }
}

void test_predict() {
  std::cout << "Testing predict method..." << std::endl;

  // Test case 1: Simple prediction
  types::samples train_samples = {{1, 2}, {3, 4}, {5, 6}};
  types::classification_targets train_targets = {0, 1, 0};
  KNN_Classifier knn(3, "manhattan");
  knn.fit(train_samples, train_targets);

  types::samples test_samples = {{2, 3}, {4, 5}};
  types::classification_targets predictions = knn.predict(test_samples);
  assert(predictions.size() == 2 &&
         "Should return predictions for all test samples");

  // Test case 2: Predict before fit
  KNN_Classifier unfitted_knn(3, "manhattan");
  try {
    unfitted_knn.predict(test_samples);
    assert(false && "Should have thrown exception for unfitted model");
  } catch (const std::invalid_argument &e) {
    // Expected exception
  }

  // Test case 3: Invalid feature dimensions
  try {
    types::samples invalid_samples = {{1, 2, 3}}; // 3 features instead of 2
    knn.predict(invalid_samples);
    assert(false &&
           "Should have thrown exception for invalid feature dimensions");
  } catch (const std::invalid_argument &e) {
    // Expected exception
  }
}

void test_predict_proba() {
  std::cout << "Testing predict_proba method..." << std::endl;

  // Test case 1: Basic probability prediction
  types::samples train_samples = {{1, 2}, {3, 4}, {5, 6}};
  types::classification_targets train_targets = {0, 1, 0};
  KNN_Classifier knn(3, "manhattan");
  knn.fit(train_samples, train_targets);

  types::samples test_samples = {{2, 3}};
  types::samples_probas probas = knn.predict_proba(test_samples);

  assert(probas.size() == 1 &&
         "Should return probabilities for all test samples");
  assert(probas[0].size() == 2 && "Should have probabilities for both classes");

  // Verify probabilities sum to 1
  double sum = 0.0;
  for (const auto &[class_label, proba] : probas[0]) {
    sum += proba;
  }
  assert(std::abs(sum - 1.0) < 1e-10 && "Probabilities should sum to 1");

  // Test case 2: Predict before fit
  KNN_Classifier unfitted_knn(3, "manhattan");
  try {
    unfitted_knn.predict_proba(test_samples);
    assert(false && "Should have thrown exception for unfitted model");
  } catch (const std::invalid_argument &e) {
    // Expected exception
  }
}

void test_distance_metrics() {
  std::cout << "Testing different distance metrics..." << std::endl;

  types::samples train_samples = {{1, 2}, {3, 4}, {5, 6}};
  types::classification_targets train_targets = {0, 1, 0};
  types::samples test_samples = {{2, 3}};

  // Test Manhattan distance
  KNN_Classifier manhattan_knn(3, "manhattan");
  manhattan_knn.fit(train_samples, train_targets);
  types::classification_targets manhattan_pred = manhattan_knn.predict(test_samples);

  // Test Euclidean distance
  KNN_Classifier euclidean_knn(3, "euclidean");
  euclidean_knn.fit(train_samples, train_targets);
  types::classification_targets euclidean_pred = euclidean_knn.predict(test_samples);

  // Test invalid metric
  try {
    KNN_Classifier invalid_knn(3, "invalid_metric");
    assert(false && "Should have thrown exception for invalid metric");
  } catch (const std::invalid_argument &e) {
    // Expected exception
  }
}

int main() {
  std::cout << "Starting KNN Classifier tests..." << std::endl;

  test_fit();
  test_predict();
  test_predict_proba();
  test_distance_metrics();

  std::cout << "All tests passed successfully!" << std::endl;
  return 0;
}
