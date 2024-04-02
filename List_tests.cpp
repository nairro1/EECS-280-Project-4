#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}

TEST(test_empty_list) {
    List<int> my_list;
    ASSERT_TRUE(my_list.empty());
    ASSERT_EQUAL(my_list.size(), 0);
}

TEST(test_push_front) {
    List<int> my_list;
    my_list.push_front(1);
    my_list.push_front(2);
    ASSERT_FALSE(my_list.empty());
    ASSERT_EQUAL(my_list.size(), 2);
    ASSERT_EQUAL(my_list.front(), 2);
}

TEST(test_push_back) {
    List<int> my_list;
    my_list.push_back(1);
    my_list.push_back(2);
    ASSERT_FALSE(my_list.empty());
    ASSERT_EQUAL(my_list.size(), 2);
    ASSERT_EQUAL(my_list.back(), 2);
}

TEST(test_pop_front) {
    List<int> my_list;
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.pop_front();
    ASSERT_FALSE(my_list.empty());
    ASSERT_EQUAL(my_list.size(), 1);
    ASSERT_EQUAL(my_list.front(), 2);
}

TEST(test_pop_back) {
    List<int> my_list;
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.pop_back();
    ASSERT_FALSE(my_list.empty());
    ASSERT_EQUAL(my_list.size(), 1);
    ASSERT_EQUAL(my_list.back(), 1);
}

TEST(test_assignment_operator) {
    // Test assignment operator on lists with the same type
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    List<int> list2;
    list2.push_back(3);
    list2.push_back(4);

    list2 = list1; // Perform assignment

    ASSERT_EQUAL(list1.size(), list2.size()); // Verify size is equal

    auto it1 = list1.begin();
    auto it2 = list2.begin();
    while (it1 != list1.end() && it2 != list2.end()) {
        ASSERT_EQUAL(*it1, *it2); // Verify elements are equal
        ++it1;
        ++it2;
    }
}





 //have a test case checking for different data types

TEST(test_clear) {
    List<int> my_list;
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.clear();
    ASSERT_TRUE(my_list.empty());
    ASSERT_EQUAL(my_list.size(), 0);
}

TEST(test_edge_cases) {
    // Test various edge cases
    List<int> my_list;

    // Insert elements
    my_list.push_front(1);
    my_list.push_front(2);
    my_list.push_back(3);
    my_list.push_back(4);

    // Remove elements
    my_list.pop_front();
    my_list.pop_back();

    // Verify size and elements
    ASSERT_EQUAL(my_list.size(), 2);
    ASSERT_EQUAL(my_list.front(), 1);
    ASSERT_EQUAL(my_list.back(), 3);
}

TEST(test_iterator) {
    List<int> my_list;

    // Insert elements
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);

    // Test iterator
    int sum = 0;
    for (auto it = my_list.begin(); it != my_list.end(); ++it) {
        sum += *it;
    }

    ASSERT_EQUAL(sum, 6); // 1 + 2 + 3 = 6
}

// Add more test cases as needed to cover other functions and edge cases
TEST(test_different_data_types) {
    // Create a list with int data type
    List<int> intList;
    intList.push_back(1);
    intList.push_back(2);

    // Create a list with char data type
    List<char> charList;
    charList.push_back('a');
    charList.push_back('b');

    // Perform assignment with the same data type
    charList = charList; // Test assignment operator with the same data type
    ASSERT_EQUAL(charList.size(), 2); // Verify size remains the same

    // Perform assignment with different data type (This will fail)
   // charList = intList; // Test assignment operator with different data type
}




TEST_MAIN()
