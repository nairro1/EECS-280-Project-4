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


TEST(test_copy_constructor) {
    // Create a list and insert elements
    List<int> originalList;
    originalList.push_back(1);
    originalList.push_back(2);
    originalList.push_back(3);

    // Create a new list using the copy constructor
    List<int> copiedList(originalList);

    // Verify that the copied list contains the same elements as the original list
    auto it1 = originalList.begin();
    auto it2 = copiedList.begin();
    while (it1 != originalList.end() && it2 != copiedList.end()) {
        ASSERT_EQUAL(*it1, *it2); // Verify elements are equal
        ++it1;
        ++it2;
    }

    // Verify that the size of the copied list is the same as the original list
    ASSERT_EQUAL(originalList.size(), copiedList.size());

    // Optionally, verify that the size of the copied list matches the expected size
    ASSERT_EQUAL(copiedList.size(), 3); // Assuming the original list has 3 elements

    // Optionally, verify that a traversal of both lists yields the same elements
    // (this check is already done inside the while loop above)
}


TEST(test_other_functions) {
    // Test the clear function
    List<int> my_list;
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.clear();
    ASSERT_TRUE(my_list.empty());
    ASSERT_EQUAL(my_list.size(), 0);

    // Test the erase function
    List<int> eraseList;
    eraseList.push_back(1);
    eraseList.push_back(2);
    eraseList.push_back(3);
    eraseList.erase(eraseList.begin()); // Erase the first element
    ASSERT_EQUAL(eraseList.size(), 2);
    ASSERT_EQUAL(eraseList.front(), 2);

    // Test the insert function
    List<int> insertList;
    insertList.push_back(1);
    insertList.push_back(3);
    auto it = insertList.begin();
    insertList.insert(++it, 2); // Insert 2 between 1 and 3
    ASSERT_EQUAL(insertList.size(), 3);
    ASSERT_EQUAL(insertList.front(), 1);
    ASSERT_EQUAL(insertList.back(), 3);
}

TEST(test_empty_list_copy_constructor) {
    List<int> emptyList;
    List<int> copiedList(emptyList);
    ASSERT_TRUE(copiedList.empty());
    ASSERT_EQUAL(copiedList.size(), 0);
}


TEST(test_single_element_list_copy_constructor) {
    List<int> singleElementList;
    singleElementList.push_back(42);
    List<int> copiedList(singleElementList);
    ASSERT_FALSE(copiedList.empty());
    ASSERT_EQUAL(copiedList.size(), 1);
    ASSERT_EQUAL(copiedList.front(), 42);
}

TEST(test_assignment_operator_self_assignment) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list = list; // Perform self-assignment
    ASSERT_EQUAL(list.size(), 2);
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 2);
}

TEST(test_erase_function) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.erase(list.begin()); // Erase the first element
    ASSERT_EQUAL(list.size(), 2);
    ASSERT_EQUAL(list.front(), 2);
}

TEST(test_insert_function) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);
    auto it = list.begin();
    auto new_it = list.insert(++it, 2); // Insert 2 between 1 and 3
    ASSERT_EQUAL(list.size(), 3);
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(*new_it, 2); // Check the value of the new iterator returned by insert
    ASSERT_EQUAL(list.back(), 3);
}



TEST(test_iterator_decrement_operator) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    auto it = list.end(); // End iterator
    --it;
    ASSERT_EQUAL(*it, 2);
}


TEST(test_iterator_increment_operator) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    auto it = list.begin();
    ++it;
    ASSERT_EQUAL(*it, 2);
}


TEST(test_iterator_equality_and_inequality) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    auto it1 = list.begin();
    auto it2 = list.begin();
    ++it2;
    ASSERT_TRUE(it1 == it1);
    ASSERT_FALSE(it1 != it1);
    ASSERT_TRUE(it1 != it2);
    ASSERT_FALSE(it1 == it2);
}

TEST(test_erase_last_element) {
    List<int> my_list;
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);
    my_list.erase(--my_list.end()); // Erase the last element
    ASSERT_EQUAL(my_list.size(), 2);
    ASSERT_EQUAL(my_list.back(), 2);
}

TEST(test_insert_beginning) {
    List<int> my_list;
    my_list.push_back(2);
    my_list.push_back(3);
    auto it = my_list.begin();
    my_list.insert(it, 1); // Insert 1 at the beginning
    ASSERT_EQUAL(my_list.size(), 3);
    ASSERT_EQUAL(my_list.front(), 1);
}





TEST_MAIN()
