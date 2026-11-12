// ============================================================
// CSCI 232 Assignment 06 – Doubly Linked List vs. std::list
// Student Implementation
// ============================================================

#include "code.hpp"
#include <algorithm>
#include <iostream>

// Uncomment the author block below and fill in your name:

std::string AUTHOR_NAME       = "Nick Badovinac";
 std::string AUTHOR_AUTHORSHIP = "I acknowledge that I have worked on this "
 "assignment independently, except where explicitly noted and referenced. "
 "Any collaboration or use of external resources has been properly cited. "
 "I am fully aware of the consequences of academic dishonesty and agree "
 "to abide by the university's academic integrity policy.";

// ============================================================
// PART 1: Class DoubleNode
// ============================================================

/// Constructor: initialize ALL THREE fields with a member initializer list.
/// value <- newValue, prevPtr <- nullptr, nextPtr <- nullptr.
DoubleNode::DoubleNode(NodeValue newValue)
    : value(newValue), prevPtr(nullptr), nextPtr(nullptr)
{
}

/// Const getter: return the stored value.
NodeValue DoubleNode::getValue() const
{
    // TODO: return the value field
    return NodeValue{value};
}

/// Const getter: return the previous node (or nullptr).
DoubleNode *DoubleNode::getPrev() const
{
    // TODO: return the prevPtr field
    return this->prevPtr;
    
}

/// Const getter: return the next node (or nullptr).
DoubleNode *DoubleNode::getNext() const
{
    
    return this->nextPtr;
}

/// Setter: store newPrevPtr in prevPtr.
void DoubleNode::setPrev(DoubleNode *newPrevPtr)
{
   this->prevPtr = newPrevPtr;
}

/// Setter: store newNextPtr in nextPtr.
void DoubleNode::setNext(DoubleNode *newNextPtr)
{
    this->nextPtr = newNextPtr;
    // TODO: assign the field
}

// ============================================================
// PART 2: Class DoublyLinkedList
// ============================================================

/// Empty list: headPtr = nullptr, tailPtr = nullptr, count = 0.
DoublyLinkedList::DoublyLinkedList()
    : headPtr(nullptr), tailPtr(nullptr), count(0)
{
}

/// RAII: delete ALL nodes. Save the next pointer BEFORE delete.
DoublyLinkedList::~DoublyLinkedList()
{
    DoubleNode* currentPtr=headPtr;

    while (currentPtr != nullptr) {
        DoubleNode* nextPtr = currentPtr->getNext();
        delete currentPtr;
        currentPtr = nextPtr;
    }
    headPtr = nullptr;
    tailPtr = nullptr;
    count = 0;
    
    // TODO: walk through the list and delete every node
}

/// Unlink the first node and RETURN it (do not delete it).
/// Fix headPtr, tailPtr, count. Clear the node's own prevPtr and nextPtr.
/// Return nullptr if the list is empty.
DoubleNode *DoublyLinkedList::detachFirst()
{
    if (headPtr == nullptr) {
        return nullptr;
    }

    DoubleNode* firstPtr = headPtr;

    headPtr = firstPtr->getNext();
    if (headPtr != nullptr) {

        headPtr->setPrev(nullptr);

    } else {
        tailPtr = nullptr;
    }

    firstPtr->setNext(nullptr);
    firstPtr->setPrev(nullptr);
    count--;
    return firstPtr;
}

/// Unlink the last node and RETURN it (do not delete it).
/// Use the tail's prev link. Return nullptr if the list is empty.
DoubleNode *DoublyLinkedList::detachLast()
{
    if (tailPtr == nullptr)  {
        return nullptr; 
    }

    DoubleNode* lastPtr = tailPtr;
    tailPtr = lastPtr->getPrev();

    if (tailPtr != nullptr) {
        tailPtr->setNext(nullptr);
    } else {
        headPtr = nullptr;
    }

    lastPtr->setNext(nullptr);
    lastPtr->setPrev(nullptr);
    count--;
    return lastPtr;
}

/// Find the FIRST node equal to value and unlink it (head, tail, only node
/// or middle node). Return nullptr if not found. Reuse detachFirst/detachLast.
DoubleNode *DoublyLinkedList::detachValue(NodeValue value)
{
    if (headPtr == nullptr) {
        return nullptr;
    }

    DoubleNode* vNode = headPtr;

    while(vNode->getValue() != value) {
        vNode = vNode->getNext();

        if(vNode == nullptr) {
            return nullptr;
        }
    }

    if (vNode == headPtr) {

        vNode = detachFirst();

    } else if (vNode == tailPtr) {

        vNode = detachLast();
        
    } else {

        DoubleNode* tempPrev;
        DoubleNode* tempNext;

        tempPrev = vNode->getPrev();
        tempPrev->setNext(vNode->getNext());

        tempNext = vNode->getNext();
        tempNext->setPrev(vNode->getPrev());

        vNode->setNext(nullptr);
        vNode->setPrev(nullptr);

    }
    count--;
    return vNode;
}

/// Create a node with new and link it in front. Handle the empty list.
void DoublyLinkedList::pushFrontValue(NodeValue value)
{

    DoubleNode* newNode = new DoubleNode(value);

    if (headPtr == nullptr) {

        headPtr = newNode;
        newNode->setNext(nullptr);
        tailPtr = newNode;

    } else if (headPtr != nullptr) {
        
        newNode->setNext(headPtr);
        headPtr->setPrev(newNode);
        headPtr=newNode;
    }


    count++;
    

}

/// Create a node with new and link it at the end. Handle the empty list.
void DoublyLinkedList::pushBackValue(NodeValue value)
{
    DoubleNode* newNode = new DoubleNode(value);

    if (headPtr == nullptr) {
        headPtr = newNode;
        newNode->setNext(nullptr);
        tailPtr = newNode;
    } else if (headPtr != nullptr) {
        tailPtr->setNext(newNode);
        newNode->setPrev(tailPtr);
        tailPtr = newNode;
    }
    count++;
    // TODO: implement
}

/// Detach the first node, read its value, delete the node, return the value.
/// Empty list -> std::nullopt.
std::optional<NodeValue> DoublyLinkedList::popFrontValue()
{

    if (headPtr == nullptr) {
        return std::nullopt;
    }

    DoubleNode* detachedNode = detachFirst();

    NodeValue detachedValue = detachedNode->getValue();

    delete detachedNode;
    return detachedValue;
    
}

/// Detach the last node, read its value, delete the node, return the value.
/// Empty list -> std::nullopt.
std::optional<NodeValue> DoublyLinkedList::popBackValue()
{
    if (headPtr == nullptr) {
        return std::nullopt;
    }
    DoubleNode* detachedNode = detachLast();
    NodeValue detachedValue = detachedNode->getValue();

    delete detachedNode;

    return detachedValue;
}

/// Remove the FIRST node equal to value and free it.
/// Return true if something was removed.
bool DoublyLinkedList::deleteValue(NodeValue value)
{
    if (headPtr == nullptr) {
        return false;
    }

    DoubleNode* vNode = detachValue(value);

    if (vNode == nullptr) {
        return false;
    }

    delete vNode;

    count--;

    return true;
}

/// Return true if any node holds value.
bool DoublyLinkedList::containsValue(NodeValue value) const
{

    if (headPtr == nullptr) {
        return false;
    }

    DoubleNode* vNode = headPtr;

    while (vNode->getValue() != value) {
        vNode = vNode->getNext();

        if (vNode->getNext() == nullptr) {
            return false;
        }
    }

    return true;
}

/// Print values head -> tail with std::visit (each followed by a space,
/// then a newline). Return the number of printed values.
int DoublyLinkedList::printForward() const
{
    DoubleNode* vNode = headPtr;
    int printed_values = 0;

    while (vNode!= nullptr) {
        std::visit([](const auto& val) {
            std::cout << val << " " << "\n";
        }, vNode->getValue());

        printed_values++;

        vNode = vNode->getNext();
    }
    return printed_values;
}

/// Print values tail -> head using prevPtr. Return the number of printed values.
int DoublyLinkedList::printBackward() const
{
    
    DoubleNode* vNode = tailPtr;
    int printed_values = 0;

    while (vNode != nullptr) {
        std::visit([](const auto& val) {
        std::cout << val << " " << "\n";
        }, vNode->getValue());

        printed_values++;

        vNode = vNode->getPrev();
    }
    return printed_values;
}

/// Return count.
int DoublyLinkedList::length() const
{
    return count;
}

// ===== BEGIN PART 3 (do not remove this marker) =====
// ============================================================
// PART 3: Class StdDoublyLinkedList
// ============================================================
// Only std::list methods, <algorithm>, iterators and std::visit.
// A loop is allowed ONLY for printing.

/// Which std::list method inserts at the front?
void StdDoublyLinkedList::pushFrontValue(NodeValue value)
{
    data.push_front(value);
}

/// Which std::list method inserts at the back?
void StdDoublyLinkedList::pushBackValue(NodeValue value)
{
    data.push_back(value);
}

/// Read the front element, remove it, return it. Empty -> std::nullopt.
std::optional<NodeValue> StdDoublyLinkedList::popFrontValue()
{
    if(data.size() == 0) {
        return std::nullopt;
    }

    NodeValue node = data.front(); // reference to the front node
    data.pop_front();

    return node;

}

/// Read the back element, remove it, return it. Empty -> std::nullopt.
std::optional<NodeValue> StdDoublyLinkedList::popBackValue()
{
    if (data.size() == 0) {
        return std::nullopt;
    }
    NodeValue node = data.back();
    data.pop_back();

    return node;
    
}

/// Remove only the FIRST element equal to value. Return true if removed.
bool StdDoublyLinkedList::deleteValue(NodeValue value)
{
    auto val = std::find(data.begin(), data.end(), value);

    if (val == data.end()) {
        return false;
    }

    data.erase(val);

    
    return true;
}

/// Search without writing your own loop.
bool StdDoublyLinkedList::containsValue(NodeValue value) const
{
    auto val = std::find(data.begin(), data.end(), value);

    if (val == data.end()) {
        return false;
    }
    return true;
}

/// Print head -> tail (same format as Part 2). Return the number of values.
int StdDoublyLinkedList::printForward() const
{
    for (auto val = data.begin(); val != data.end(); ++val) {
        std::visit([](const auto& vval) {
            std::cout << vval << " ";
        }, *val);
    }
    return data.size();
}

/// Print tail -> head (same format as Part 2). Return the number of values.
int StdDoublyLinkedList::printBackward() const
{
    for (auto val = data.end(); val != data.end(); ++val) {
        std::visit([](const auto& vval) {
            std::cout << vval << " ";
        }, *val);
    }
    return data.size();
}

/// size() returns size_t, length() returns int.
int StdDoublyLinkedList::length() const
{
    
    return data.size();
}
// ===== END PART 3 (do not remove this marker) =====
