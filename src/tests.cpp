#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <iostream>

// ============================================================
// PART 2 Tests: DoublyLinkedList
// ============================================================

/// Create a DoublyLinkedList. Verify length() is 0 on a new list.
void test_new_list_is_empty(void)
{
    DoublyLinkedList llist;

    TEST_ASSERT_TRUE_MESSAGE(llist.length() == 0, "Error: list length is not equal to 0");
}

/// Create a DoublyLinkedList. Call pushFrontValue and pushBackValue.
/// Verify length() is 2.
void test_push_increases_length(void)
{
    DoublyLinkedList llist;

    llist.pushFrontValue(7);
    llist.pushBackValue(8);
    TEST_ASSERT_TRUE_MESSAGE(llist.length() == 2, "Error: list length is not equal to 2");
}

/// Create an EMPTY DoublyLinkedList.
/// Verify popFrontValue() and popBackValue() both have NO value (has_value() is false).
void test_pop_on_empty_list(void)
{
    DoublyLinkedList llist;

    TEST_ASSERT_TRUE_MESSAGE(llist.popFrontValue().has_value() == false, "Error: popFrontValue() has a value");
    TEST_ASSERT_TRUE_MESSAGE(llist.popBackValue().has_value() == false, "Error: popBackValue has a value");

}

/// Push 1, 2, 3 with pushBackValue.
/// Verify popBackValue() gives 3, then popFrontValue() gives 1, then length() is 1.
void test_pop_order(void)
{
    DoublyLinkedList llist;

    llist.pushBackValue(1);
    llist.pushBackValue(2);
    llist.pushBackValue(3);
    
    TEST_ASSERT_TRUE_MESSAGE(std::get<int>(llist.popBackValue().value()) == 3, "Error: popBackValue() does not return 3");
    TEST_ASSERT_TRUE_MESSAGE(std::get<int>(llist.popFrontValue().value()) == 1, "Error: popFrontValue() does not return 1");
    TEST_ASSERT_TRUE_MESSAGE(llist.length() == 1, "Error: length is not 1");
}

/// Push one value, then call deleteValue with a value that is NOT in the list.
/// Verify it returns false and length() does not change.
void test_delete_value_not_found(void)
{
    DoublyLinkedList llist;
    bool status;
    llist.pushFrontValue(1);
    status = llist.deleteValue(5);


    TEST_ASSERT_TRUE_MESSAGE(status == false, "Error: status did not return false");
    TEST_ASSERT_TRUE_MESSAGE(llist.length() == 1, "Error: length is not 1");

}

/// Push 1, 2, 3 with pushBackValue. Call deleteValue(2).
/// Verify popBackValue() gives 3 and the next popBackValue() gives 1.
/// (popBackValue follows prevPtr: this fails if you forgot to repair the backward link.)
void test_delete_middle_keeps_links(void)
{
    DoublyLinkedList llist;

    llist.pushBackValue(1);
    llist.pushBackValue(2);
    llist.pushBackValue(3);

    llist.deleteValue(2);


    TEST_ASSERT_TRUE_MESSAGE(std::get<int>(llist.popBackValue().value()) == 3, "Error: popBackValue is not 3");
    TEST_ASSERT_TRUE_MESSAGE(std::get<int>(llist.popBackValue().value()) == 1, "Error: second instance of popBackValue is not 1");

}

// ============================================================
// PART 3 Tests: StdDoublyLinkedList
// ============================================================

/// Push 1, 2, 1 with pushBackValue. Call deleteValue(NodeValue{1}).
/// Verify length() is 2 and popFrontValue() gives 2 (only the FIRST 1 was removed).
void test_std_delete_only_first(void)
{
    StdDoublyLinkedList llist;
    llist.pushBackValue(NodeValue{1});
    llist.pushBackValue(2);
    llist.pushBackValue(1);

    llist.deleteValue(NodeValue{1});
    
    int len = llist.length();
    auto val = std::get<int>(llist.popFrontValue().value());

    
    TEST_ASSERT_TRUE_MESSAGE(val == 2, "Error: popFrontValue does not give 2");
    TEST_ASSERT_TRUE_MESSAGE(len == 2, "Error: length is not 2");
}

/// Create an EMPTY StdDoublyLinkedList.
/// Verify popFrontValue() and popBackValue() have NO value and do not crash.
void test_std_pop_on_empty_list(void)
{
    StdDoublyLinkedList llist;


    TEST_ASSERT_TRUE_MESSAGE(llist.popBackValue().has_value() == false, "TODO: Implement this test");
    TEST_ASSERT_TRUE_MESSAGE(llist.popFrontValue().has_value() == false, "TODO: Implement this test");

}


