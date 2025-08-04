#include <gtest/gtest.h>
#include <adastra/core/algorithms/Search.hpp>
#include <vector>
#include <algorithm>

using adastra::core::algorithms::Search;

TEST(SearchAlgorithms, BinarySearchFound)
{
    std::vector<int> data = {1, 3, 5, 7, 9};
    int result = Search<int>::binarySearch(data, 5);
    EXPECT_EQ(result, 2); // 5 est à l'index 2
}

TEST(SearchAlgorithms, BinarySearchNotFound)
{
    std::vector<int> data = {1, 3, 5, 7, 9};
    int result = Search<int>::binarySearch(data, 6);
    EXPECT_EQ(result, -1); // 6 n'est pas dans le vecteur
}

TEST(SearchAlgorithms, CountingSort)
{
    std::vector<int> data = {4, 2, 2, 8, 3, 3, 1};
    std::vector<int> expected = {1, 2, 2, 3, 3, 4, 8};

    Search<int>::countingSort(data);
    EXPECT_EQ(data, expected);
}

TEST(SearchAlgorithms, Fibonacci)
{
    EXPECT_EQ(Search<int>::fibonacci(0), 0);
    EXPECT_EQ(Search<int>::fibonacci(1), 1);
    EXPECT_EQ(Search<int>::fibonacci(10), 55);
}

TEST(SearchAlgorithms, MergeSort)
{
    std::vector<int> data = {5, 1, 4, 2, 8};
    std::vector<int> expected = data;
    std::sort(expected.begin(), expected.end());

    Search<int>::mergeSort(data, 0, data.size() - 1);
    EXPECT_EQ(data, expected);
}
