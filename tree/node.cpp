#include "node.hpp"

#include <iostream>
using std::clog;
using std::endl;

#include "utility.hpp"

template<copy_orderable T>
node<T>::node() : pParent(nullptr), pLeft(nullptr), pRight(nullptr), myColor(color_t::black)
{
}

template<copy_orderable T>
node<T>::node(const T& item) : node(), myItem(item)
{
}

template<copy_orderable T>
node<T>::node(T&& item) : node(), myItem(item)
{
}

template<copy_orderable T>
node<T>::~node()
{
    clog << "~node() -> " << enclose(myItem, '[') << endl;
    clog << "- left is " << enclose((pLeft ? pLeft->myItem : "null"), '[') << endl;
    clog << "- right is " << enclose((pRight ? pRight->myItem : "null"), '[') << endl;
}

template <copy_orderable T>
void node<T>::set_child(child_t child, shared_ptr<node> pNewChild)
{
    shared_ptr<node>& pChild{ (child == child_t::left) ? pLeft : pRight };

    pChild = pNewChild;
}

template <copy_orderable T>
void node<T>::set_color(color_t color)
{
    myColor = color;

    clog << "node " << enclose(myItem, '[') << " is now ";
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
