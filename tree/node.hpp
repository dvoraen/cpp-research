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
using std::clog;
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
    explicit node(T&& item);
    ~node();

    shared_ptr<node> left() const;
    shared_ptr<node> right() const;
    shared_ptr<node> up() const;

    const T& item() const;

    void set_child(child_t child, shared_ptr<node<T>> pNewChild);
    void set_parent(shared_ptr<node<T>>& pNewParent);
    void set_color(color_t color);

    void rotate_left();
    void rotate_right();

    string color_text() const;

private:
    shared_ptr<node> pLeft;
    shared_ptr<node> pRight;
    weak_ptr<node> pParent;

    T myItem;

    color_t myColor;

    shared_ptr<node> sibling() const;
    shared_ptr<node> uncle() const;
    shared_ptr<node> successor() const;

};

// ----------------------
// node<T> inline methods
// ----------------------
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
inline shared_ptr<node<T>> node<T>::up() const
{
    if (pParent)
        return pParent->lock();

    return nullptr;
}

template <copy_orderable T>
inline const T& node<T>::item() const
{
    return myItem;
}

template <copy_orderable T>
inline string node<T>::color_text() const
{
    return (myColor == color_t::black ? "black" : "red");
}

// ostream& operator << (ostream& os, node::child_t child);
// ostream& operator << (ostream& os, node::color_t color);

// ------------------
// node<T> definition
// ------------------

template<copy_orderable T>
node<T>::node() : pLeft(nullptr), pRight(nullptr), myColor(color_t::black)
{
}

template<copy_orderable T>
node<T>::node(const T& item) : pLeft(nullptr), pRight(nullptr), myColor(color_t::black), myItem(item)
{
}

template<copy_orderable T>
node<T>::node(T&& item) : node(item)
{
}

template<copy_orderable T>
node<T>::~node()
{
    string myItemStr = std::to_string(myItem);
    string leftItemStr = pLeft ? std::to_string(pLeft->item()) : "null";
    string rightItemStr = pRight ? std::to_string(pRight->item()) : "null";

    clog << "~node() -> " << enclose(myItemStr, '[') << endl;
    clog << "- left is " << enclose(leftItemStr, '[') << endl;
    clog << "- right is " << enclose(rightItemStr, '[') << endl;
}

template <copy_orderable T>
void node<T>::set_child(child_t child, shared_ptr<node> pNewChild)
{
    shared_ptr<node>& pChild{ (child == child_t::left) ? pLeft : pRight };

    pChild = pNewChild;
}

template<copy_orderable T>
inline void node<T>::set_parent(shared_ptr<node<T>>& pNewParent)
{
    pParent = pNewParent;
}

template <copy_orderable T>
void node<T>::set_color(color_t color)
{
    myColor = color;

    clog << "node " << enclose(std::to_string(myItem), '[') << " is now ";
    // "node [n] is now "
    clog << enclose(this->color_text(), '<');
    // "node [n] is now <black/red>"
    clog << endl;
}

template <copy_orderable T>
void node<T>::rotate_left()
{
    clog << "rotate_left() at " << enclose(myItem, '[') << endl;
    // "rotate_left() at [n]"
}

template <copy_orderable T>
void node<T>::rotate_right()
{
    clog << "rotate_right() at " << enclose(myItem, '[') << endl;
    // "rotate_right() at [n]"
}

template <copy_orderable T>
shared_ptr<node<T>> node<T>::sibling() const
{
    if (!pParent)
        return nullptr;

    shared_ptr<node> pSharedParent = pParent->lock();

    // if this is parent's left child; return right child
    // BUG: this ptr won't be equal to a shared_ptr, necessarily
    if (this == pSharedParent->left().get())
        return pSharedParent->right();
    else
        return pSharedParent->left();
}

template <copy_orderable T>
shared_ptr<node<T>> node<T>::uncle() const
{
    return (pParent ? pParent->lock()->sibling() : nullptr);
}

template <copy_orderable T>
shared_ptr<node<T>> node<T>::successor() const
{
    if (!this->right())
        return nullptr;

    // successor is the left-most node of the right subtree
    shared_ptr<node> pCurrent = this->right();

    while (pCurrent->left())
        pCurrent = pCurrent->left();

    clog << "successor of " << enclose(this->myItem, '[') << " is ";
    // "successor of [n] is "
    clog << enclose(pCurrent->myItem, ']') << endl;
    // "successor of [n] is [x]"

    return pCurrent;
}

#endif
