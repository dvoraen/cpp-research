#pragma once

#ifndef __node_hpp__
#define __node_hpp__

#include "concepts.hpp"

#include <memory>
using std::shared_ptr;
using std::weak_ptr;

#include <string>
using std::string;

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;

#include "utility.hpp"

template <copy_orderable T>
class node
{
public:
    enum class child_t { left, right };
    enum class color_t { red, black };

    node();
    explicit node(const T& item);
    ~node();

    shared_ptr<node<T>> left() const;
    shared_ptr<node<T>> right() const;
    shared_ptr<node<T>> parent() const;

    const T& get_item() const noexcept;

    void set_child(child_t child, shared_ptr<node<T>> pNewChild);
    void set_parent(shared_ptr<node<T>>& pNewParent);
    void set_color(color_t color);

    bool is_red() const noexcept;
    bool is_black() const noexcept;
    bool is_left() const;
    bool is_right() const;

    void rotate_left();
    void rotate_right();

    string color_text() const;
    void status() const;

private:
    shared_ptr<node<T>> pLeft;
    shared_ptr<node<T>> pRight;
    weak_ptr<node<T>> pParent;

    T myItem;

    color_t myColor;

    shared_ptr<node<T>> sibling() const;
    shared_ptr<node<T>> uncle() const;
    shared_ptr<node<T>> grandparent() const;
    shared_ptr<node<T>> successor() const;
};

// ------------------
// node<T> definition
// ------------------

template<copy_orderable T>
node<T>::node() : pLeft{ nullptr }, pRight{ nullptr }, myColor{ color_t::red }
{
}

template<copy_orderable T>
node<T>::node(const T& item) : pLeft{ nullptr }, pRight{ nullptr }, myColor{ color_t::red }, myItem{ item }
{
}

template<copy_orderable T>
node<T>::~node()
{
    auto myItemStr{ std::to_string(myItem) };

    cout << "~node" << enclose(myItemStr, '(') << endl;
}

template <copy_orderable T>
inline shared_ptr<node<T>> node<T>::left() const
{
    return pLeft;
}

template <copy_orderable T>
inline shared_ptr<node<T>> node<T>::right() const
{
    return pRight;
}

template <copy_orderable T>
inline shared_ptr<node<T>> node<T>::parent() const
{
    return (!pParent.expired() ? pParent.lock() : nullptr);
}

template <copy_orderable T>
inline const T& node<T>::get_item() const noexcept
{
    return myItem;
}

template <copy_orderable T>
inline void node<T>::set_child(child_t child, shared_ptr<node<T>> pNewChild)
{
    shared_ptr<node<T>>& pChild{ (child == child_t::left) ? pLeft : pRight };

    pChild = pNewChild;
}

template<copy_orderable T>
inline void node<T>::set_parent(shared_ptr<node<T>>& pNewParent)
{
    pParent = pNewParent;
}

template <copy_orderable T>
inline void node<T>::set_color(color_t color)
{
    myColor = color;
}

template<copy_orderable T>
inline bool node<T>::is_red() const noexcept
{
    return (myColor == color_t::red);
}

template<copy_orderable T>
inline bool node<T>::is_black() const noexcept
{
    return (myColor == color_t::black);
}

template<copy_orderable T>
inline bool node<T>::is_left() const
{
    return (!pParent.expired() ? (this == this->parent()->left().get()) : false);
}

template<copy_orderable T>
inline bool node<T>::is_right() const
{
    return (!pParent.expired() ? (this == this->parent()->right().get()) : false);
}

// ostream& operator << (ostream& os, node::child_t child);
// ostream& operator << (ostream& os, node::color_t color);

template <copy_orderable T>
void node<T>::rotate_left()
{
    // rotating left leads to the following effects :
    // - this node's new parent is the former right child
    // - this node's left child is unchanged
    // - this node's new right child is its successor
    // - this node is the new parent's left child
    // - the new parent's parent is this node's old parent

    auto pOldParent{ pParent };
    auto pNewParent{ pRight };

    this->set_parent(pNewParent);
    // left child is unchanged
    // new parent's left child is this node
    this->set_child(child_t::right, pNewParent->left());
    pNewParent->set_parent(pOldParent);

    cout << "rotate_left() at " << enclose(myItem, '[') << endl;
    // "rotate_left() at [n]"
    this->status();
}

template <copy_orderable T>
void node<T>::rotate_right()
{
    auto pOldParent{ pParent };
    auto pNewParent{ pLeft };

    this->set_parent(pNewParent);
    // right child is unchanged
    // this node's left child is new parent's current left child
    // new parent's new left child is this node
    pNewParent->set_parent(pOldParent);

    cout << "rotate_right() at " << enclose(myItem, '[') << endl;
    // "rotate_right() at [n]"

    this->status();
}

template <copy_orderable T>
inline string node<T>::color_text() const
{
    return (myColor == color_t::black ? "black" : "red");
}

template<copy_orderable T>
void node<T>::status() const
{
    auto myItemStr{ std::to_string(myItem) };
    auto parentItemStr{ pParent.expired() ? "null" : std::to_string(pParent.lock()->get_item()) };
    auto leftItemStr{ pLeft ? std::to_string(pLeft->get_item()) : "null" };
    auto rightItemStr{ pRight ? std::to_string(pRight->get_item()) : "null" };

    cout << std::boolalpha;
    cout << "node " << enclose(myItemStr, '[') << " -- ";
    cout << "parent: " << enclose(parentItemStr, '(') << " -- ";
    cout << "left: " << enclose(leftItemStr, '<') << ' ';
    cout << "right: " << enclose(rightItemStr, '<') << " -- ";
    cout << "(is_left: " << this->is_left() << " is_right: " << this->is_right() << ')' << endl;
}

// node<T> private methods

template <copy_orderable T>
shared_ptr<node<T>> node<T>::sibling() const
{
    if (pParent.expired())
        return nullptr;

    shared_ptr<node<T>> pSharedParent{ pParent.lock() };

    // if this is parent's left child; return right child
    if (this == pSharedParent->left().get())
        return pSharedParent->right();
    else
        return pSharedParent->left();
}

template <copy_orderable T>
inline shared_ptr<node<T>> node<T>::uncle() const
{
    return (!pParent.expired() ? this->parent()->sibling() : nullptr);
}

template<copy_orderable T>
inline shared_ptr<node<T>> node<T>::grandparent() const
{
    return (!pParent.expired() ? this->parent()->parent() : nullptr);
}

template <copy_orderable T>
shared_ptr<node<T>> node<T>::successor() const
{
    if (!pRight)
        return nullptr;

    // successor is the left-most node of the right subtree
    shared_ptr<node<T>> pCurrent{ pRight };

    while (pCurrent->left())
        pCurrent = pCurrent->left();

    auto myItemStr{ std::to_string(this->get_item()) };
    auto successorStr{ std::to_string(pCurrent->get_item()) };

    cout << "successor of " << enclose(myItemStr, '[') << " is ";
    // "successor of [n] is "
    cout << enclose(successorStr, '<') << endl;
    // "successor of [n] is <x>"

    return pCurrent;
}

#endif
