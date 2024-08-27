#include "containers/bidirectional_list_container.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <list>

struct BidirectionalListFixture : public testing::Test {

  const size_t sizeList = 10;
  BidirectionalListContainer<size_t> list; // the same list instance for all
                                           // test cases

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

    // Create list with elementCount elements
    for (size_t i = 0; i < sizeList; ++i) {
      list.push_back(i);
    }
  }

  // You can define per-test tear-down logic as usual.
  void TearDown() override {
    //    std::cout << "TearDown" << std::endl;
    while (list.size()) {
      list.erase(0);
    }
    // Nothing to do for now
  }
};

TEST_F(BidirectionalListFixture, CreateEmpty) {
  try {
    // Act
    BidirectionalListContainer<size_t> list2;
    // Assert
    ASSERT_TRUE(true);
  } catch (std::exception &ex) {
    std::cerr << "Exception in CreateEmpty: " << ex.what() << std::endl;
    // Assert
    ASSERT_TRUE(false);
  }
}

TEST_F(BidirectionalListFixture, PushFront) {
  // Act
  list.push_front(55);

  // Assert
  ASSERT_EQ(list[0], 55);
  ASSERT_EQ(list.size(), sizeList + 1);
}

TEST_F(BidirectionalListFixture, Insert) {
  // Act
  list.insert(5, 77);

  // Assert
  ASSERT_EQ(list[5], 77);
  ASSERT_EQ(list.size(), sizeList + 1);
}

TEST_F(BidirectionalListFixture, PushBack) {
  // Act
  list.push_back(33);

  // Assert
  ASSERT_EQ(list[list.size() - 1], 33);
  ASSERT_EQ(list.size(), sizeList + 1);
}

TEST_F(BidirectionalListFixture, Erase) {
  // Arrange
  std::vector<size_t> erase_idx{3, 5, 7};
  std::list<size_t> list_after_erase;
  for (size_t i = 0; i < sizeList; ++i) {
    list_after_erase.push_back(i);
  }

  for (size_t i = 0; i < erase_idx.size(); i++) {
    auto iter = list_after_erase.begin();
    std::advance(iter, (erase_idx[i] - (i + 1)));
    list_after_erase.erase(iter);
  }

  // Act
  for (size_t i = 0; i < erase_idx.size(); i++) {
    list.erase(erase_idx[i] - (i + 1));
  }

  // Assert
  ASSERT_EQ(list.size(), list_after_erase.size());

  for (size_t i = 0; i < list.size(); i++) {
    auto iter = list_after_erase.begin();
    std::advance(iter, i);
    ASSERT_EQ(list[i], *iter);
  }
}

TEST_F(BidirectionalListFixture, OperatorGet) {
  // Arrange
  std::list<size_t> ideal_list;
  for (size_t i = 0; i < sizeList; ++i) {
    ideal_list.push_back(i);
  }

  // Act

  // Assert
  ASSERT_EQ(list.size(), ideal_list.size());
  for (size_t i = 0; i < list.size(); i++) {
    auto iter = ideal_list.begin();
    std::advance(iter, i);
    ASSERT_EQ(list[i], *iter);
  }
}

TEST_F(BidirectionalListFixture, Iterator) {
  // Arrange
  std::list<size_t> ideal_list;
  for (size_t i = 0; i < sizeList; ++i) {
    ideal_list.push_back(i);
  }

  // Act

  // Assert
  ASSERT_EQ(list.size(), ideal_list.size());
  int j = 0;
  for (auto i = list.begin(); i != list.end(); ++i, ++j) {
    auto iter = ideal_list.begin();
    std::advance(iter, j);
    ASSERT_EQ(*i, *iter);
  }
}

TEST_F(BidirectionalListFixture, GetSize) {
  // Arrange

  // Act

  // Assert
  ASSERT_EQ(list.size(), sizeList);
}

TEST_F(BidirectionalListFixture, CopyCtor) {
  // Arrange

  // Act
  BidirectionalListContainer<size_t> list2{list};
  BidirectionalListContainer<size_t> list3;
  list3 = list;

  // Assert
  ASSERT_EQ(list.size(), list2.size());
  ASSERT_EQ(list.size(), list3.size());
  for (size_t i = 0; i < list.size(); i++) {
    ASSERT_EQ(list[i], list2[i]);
    ASSERT_EQ(list[i], list3[i]);
  }
}

TEST_F(BidirectionalListFixture, Molist) {
  // Arrange
  BidirectionalListContainer<size_t> list2{list};
  BidirectionalListContainer<size_t> list3{list};

  // Act
  BidirectionalListContainer<size_t> list4{std::move(list2)};
  BidirectionalListContainer<size_t> list5;
  list5 = std::move(list3);

  // Assert
  ASSERT_EQ(list2.size(), 0);
  ASSERT_EQ(list3.size(), 0);
  ASSERT_EQ(list.size(), list4.size());
  ASSERT_EQ(list.size(), list5.size());
  for (size_t i = 0; i < list.size(); i++) {
    ASSERT_EQ(list[i], list4[i]);
    ASSERT_EQ(list[i], list5[i]);
  }
}

TEST_F(BidirectionalListFixture, Destructor) {
  // Arrange

  // Act
  list.~BidirectionalListContainer();

  // Assert
  ASSERT_EQ(list.size(), 0);
}
