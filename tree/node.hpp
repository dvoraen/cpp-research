#pragma once

#ifndef __node_hpp__
#define __node_hpp__

#include "concepts.hpp"

#include <memory>
using std::shared_ptr;
using std::weak_ptr;

#include <string>
using std::string;

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

    void set_child(child_t child, shared_ptr<node> pNewChild);
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
    return (myColor == child_t::black ? "black" : "red");
}

// ostream& operator << (ostream& os, node::child_t child);
// ostream& operator << (ostream& os, node::color_t color);

#endif
