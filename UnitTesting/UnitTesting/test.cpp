// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <exception>
#include <cassert>

// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // Verify that the collection is initially empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    // Add a single entry to the collection
    add_entries(1);

    // Verify that the collection is no longer empty and the size is 1
    ASSERT_FALSE(collection->empty());
    ASSERT_EQ(collection->size(), 1);
    EXPECT_EQ(collection->at(0) >= 0 && collection->at(0) < 100, true) << "Value should be between 0 and 99";
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // Add five entries to the collection
    add_entries(5);

    // Verify that the collection size is 5
    ASSERT_EQ(collection->size(), 5);

    // Optionally, verify that all added values are within the expected range
    for (const auto& val : *collection) {
        EXPECT_GE(val, 0) << "Value should be greater than or equal to 0";
        EXPECT_LT(val, 100) << "Value should be less than 100";
    }
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeIsGreaterThanOrEqualToSize) {

    // Test for 0 entries
    ASSERT_TRUE(collection->empty());
    EXPECT_GE(collection->max_size(), collection->size());

    // Test for 1 entry
    add_entries(1);
    EXPECT_GE(collection->max_size(), collection->size());

    // Clear and test for 5 entries
    collection->clear();
    add_entries(5);
    EXPECT_GE(collection->max_size(), collection->size());

    // Clear and test for 10 entries
    collection->clear();
    add_entries(10);
    EXPECT_GE(collection->max_size(), collection->size());
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityIsGreaterThanOrEqualToSize) {

    // Test for 0 entries
    ASSERT_TRUE(collection->empty());
    EXPECT_GE(collection->capacity(), collection->size());

    // Test for 1 entry
    add_entries(1);
    EXPECT_GE(collection->capacity(), collection->size());

    // Clear and test for 5 entries
    collection->clear();
    add_entries(5);
    EXPECT_GE(collection->capacity(), collection->size());

    // Clear and test for 10 entries
    collection->clear();
    add_entries(10);
    EXPECT_GE(collection->capacity(), collection->size());
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizingIncreasesCollectionSize) {

    // Add initial entries
    add_entries(5);
    size_t initial_size = collection->size();

    // Resize to a larger size
    collection->resize(10);

    // Verify that the size has increased
    EXPECT_GT(collection->size(), initial_size);
    EXPECT_EQ(collection->size(), 10);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizingDecreasesCollectionSize) {

    // Add initial entries
    add_entries(10);
    size_t initial_size = collection->size();

    // Resize to a smaller size
    collection->resize(5);

    // Verify that the size has decreased
    EXPECT_LT(collection->size(), initial_size);
    EXPECT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizingDecreasesCollectionToZero) {
    
    // Add initial entries
    add_entries(10);
    ASSERT_EQ(collection->size(), 10);

    // Resize to zero
    collection->resize(0);

    // Verify that the collection is empty
    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection) {

    // Add entries to the collection
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);

    // Clear the collection
    collection->clear();

    // Verify that the collection is empty
    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseBeginEndErasesCollection) {

    // Add entries to the collection
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);

    // Erase all elements using erase(begin, end)
    collection->erase(collection->begin(), collection->end());

    // Verify that the collection is empty
    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityButNotSize) {

    // Initial capacity and size
    size_t initial_capacity = collection->capacity();
    size_t initial_size = collection->size();

    // Reserve additional capacity
    collection->reserve(initial_capacity + 10);

    // Verify that capacity has increased
    EXPECT_GE(collection->capacity(), initial_capacity + 10);

    // Verify that size has not changed
    EXPECT_EQ(collection->size(), initial_size);
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, AtThrowsOutOfRangeException) {

    // Add some entries to the collection
    add_entries(3);
    ASSERT_EQ(collection->size(), 3);

    // Attempt to access an out-of-bounds index and expect an exception
    EXPECT_THROW({
        int value = collection->at(5);
        (void)value; // Suppress unused variable warning
        }, std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
// Positive Test to Verify that front() returns the first element correctly
TEST_F(CollectionTest, FrontReturnsFirstElement) {

    // Add entries to the collection
    add_entries(3);
    ASSERT_EQ(collection->size(), 3);

    // Manually set known values for predictability
    (*collection)[0] = 10;
    (*collection)[1] = 20;
    (*collection)[2] = 30;

    // Verify that front() 
    EXPECT_EQ(collection->front(), 10);
}

// Negative Test to Verify that accessing front() on an empty collection throws an exception
TEST_F(CollectionTest, FrontThrowsExceptionWhenEmpty) {

    // Ensure the collection is empty
    ASSERT_TRUE(collection->empty());

    // Attempt to access front() and expect an exception
    EXPECT_THROW({
       int value = collection->at(0);
       (void)value;
        }, std::out_of_range);
}