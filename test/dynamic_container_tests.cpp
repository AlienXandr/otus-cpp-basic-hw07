#include "containers/dynamic_container.hpp"
#include <gtest/gtest.h>
#include <iostream>

struct DynamicVectorFixture : public testing::Test {

  const size_t sizeVector = 10;
  DynamicContainer<size_t> vector; // the same vector instance for all test
                                   // cases

  // Per-test-suite set-up.
  static void SetUpTestSuite() {
    //    std::cout << "SetUpTestSuite" << std::endl;
  }

  // Per-test-suite tear-down.
  static void TearDownTestSuite() {
    //    std::cout << "TearDownTestSuite" << std::endl;
  }

  // Per-test set-up
  void SetUp() override {
    //    std::cout << "SetUp" << std::endl;

    // Create vector with elementCount elements
    for (size_t i = 0; i < sizeVector; ++i) {
      vector.push_back(i);
    }
  }

  // You can define per-test tear-down logic as usual.
  void TearDown() override {
    //    std::cout << "TearDown" << std::endl;
    while (vector.size()) {
      vector.erase(0);
    }
    // Nothing to do for now
  }
};

TEST_F(DynamicVectorFixture, CreateEmpty) {
  try {
    // Act
    DynamicContainer<size_t> vector2;
    // Assert
    ASSERT_TRUE(true);
  } catch (std::exception &ex) {
    std::cerr << "Exception in CreateEmpty: " << ex.what() << std::endl;
    // Assert
    ASSERT_TRUE(false);
  }
}

TEST_F(DynamicVectorFixture, CreateVeryBig) {
  try {
    // Act
    DynamicContainer<size_t> vector2{size_t(1e15)};
    // Assert
    ASSERT_TRUE(false);
  } catch (std::exception &ex) {
    std::cerr << "Exception in CreateVeryBig: " << ex.what() << std::endl;
    // Assert
    ASSERT_TRUE(true);
  }
}

TEST_F(DynamicVectorFixture, PushFront) {
  // Act
  vector.push_front(55);

  // Assert
  ASSERT_EQ(vector[0], 55);
  ASSERT_EQ(vector.size(), sizeVector + 1);
}

TEST_F(DynamicVectorFixture, Insert) {
  // Act
  vector.insert(5, 77);

  // Assert
  ASSERT_EQ(vector[5], 77);
  ASSERT_EQ(vector.size(), sizeVector + 1);
}

TEST_F(DynamicVectorFixture, PushBack) {
  // Act
  vector.push_back(33);

  // Assert
  ASSERT_EQ(vector[vector.size() - 1], 33);
  ASSERT_EQ(vector.size(), sizeVector + 1);
}

TEST_F(DynamicVectorFixture, Erase) {
  // Arrange
  std::vector<size_t> erase_idx{3, 5, 7};
  std::vector<size_t> vector_after_erase;
  for (size_t i = 0; i < sizeVector; ++i) {
    vector_after_erase.push_back(i);
  }
  for (size_t i = 0; i < erase_idx.size(); i++) {
    vector_after_erase.erase(vector_after_erase.begin() +
                             (erase_idx[i] - (i + 1)));
  }

  // Act
  for (size_t i = 0; i < erase_idx.size(); i++) {
    vector.erase(erase_idx[i] - (i + 1));
  }

  // Assert
  ASSERT_EQ(vector.size(), vector_after_erase.size());
  for (size_t i = 0; i < vector.size(); i++) {
    ASSERT_EQ(vector[i], vector_after_erase[i]);
  }
}

TEST_F(DynamicVectorFixture, OperatorGet) {
  // Arrange
  std::vector<size_t> ideal_vector;
  for (size_t i = 0; i < sizeVector; ++i) {
    ideal_vector.push_back(i);
  }

  // Act

  // Assert
  ASSERT_EQ(vector.size(), ideal_vector.size());
  for (size_t i = 0; i < vector.size(); i++) {
    ASSERT_EQ(vector[i], ideal_vector[i]);
  }
}

TEST_F(DynamicVectorFixture, Iterator) {
  // Arrange
  std::vector<size_t> ideal_vector;
  for (size_t i = 0; i < sizeVector; ++i) {
    ideal_vector.push_back(i);
  }

  // Act

  // Assert
  ASSERT_EQ(vector.size(), ideal_vector.size());
  int j = 0;
  for (auto i = vector.begin(); i != vector.end(); ++i, ++j) {
    ASSERT_EQ(*i, ideal_vector[j]);
  }
}

TEST_F(DynamicVectorFixture, GetSize) {
  // Arrange

  // Act

  // Assert
  ASSERT_EQ(vector.size(), sizeVector);
}

TEST_F(DynamicVectorFixture, CopyCtor) {
  // Arrange

  // Act
  DynamicContainer<size_t> vector2{vector};
  DynamicContainer<size_t> vector3;
  vector3 = vector;

  // Assert
  ASSERT_EQ(vector.size(), vector2.size());
  ASSERT_EQ(vector.size(), vector3.size());
  for (size_t i = 0; i < vector.size(); i++) {
    ASSERT_EQ(vector[i], vector2[i]);
    ASSERT_EQ(vector[i], vector3[i]);
  }
}

TEST_F(DynamicVectorFixture, MoveCtor) {
  // Arrange
  DynamicContainer<size_t> vector2{vector};
  DynamicContainer<size_t> vector3{vector};

  // Act
  DynamicContainer<size_t> vector4{std::move(vector2)};
  DynamicContainer<size_t> vector5;
  vector5 = std::move(vector3);

  // Assert
  ASSERT_EQ(vector2.size(), 0);
  ASSERT_EQ(vector3.size(), 0);
  ASSERT_EQ(vector.size(), vector4.size());
  ASSERT_EQ(vector.size(), vector5.size());
  for (size_t i = 0; i < vector.size(); i++) {
    ASSERT_EQ(vector[i], vector4[i]);
    ASSERT_EQ(vector[i], vector5[i]);
  }
}

TEST_F(DynamicVectorFixture, Destructor) {
  // Arrange

  // Act
  vector.~DynamicContainer();

  // Assert
  ASSERT_EQ(vector.size(), 0);
}
