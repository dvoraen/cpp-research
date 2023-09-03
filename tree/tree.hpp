// tree.hpp
// Ian Haley

// Templatized, STL-compatible, self-balancing binary search tree

// TODO: concepts for T?

#pragma once

#ifndef __tree_hpp__
#define __tree_hpp__

#include <concepts>
#include <compare>
#include <memory>

using std::shared_ptr;
using std::weak_ptr;
using std::unique_ptr;

// TODO: Audit changes to weak_ptr<node>
// TODO: Replace remaining node* uses with weak_ptr<node>


template <typename T>
concept copy_orderable = std::totally_ordered<T> && std::copyable<T>;

// Binary search tree.
// Requirements on T:
// - totally_ordered -- T must support < > <= >= == !=
// - copyable -- T can be copied and moved
template <copy_orderable T>
class tree
{
public:
    tree();
    explicit tree(const tree<T>& tree);
    explicit tree(tree<T>&& tree) noexcept; // unsure if needed
    ~tree();

    void insert(const T& item);
    // void insert(T&& item);
    // void insert(InputIt first, InputIt last);

    void erase(const T& item);
    void clear() noexcept;

    bool contains(const T& item) const;

    size_t size() const noexcept;
    bool empty() const noexcept;

private:
    class node; // forward declaration; definition below

    shared_ptr<node> pRoot; // root of tree    
    size_t mySize; // size of tree

    // void balance(); // Balance the binary tree according to red-black rules.
    const shared_ptr<node> find(const T& item) const;
};

template <copy_orderable T>
class tree<T>::node
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
// tree<T> inline methods
// ----------------------
template <copy_orderable T>
inline size_t tree<T>::size() const noexcept
{
    return mySize;
}

template <copy_orderable T>
inline bool tree<T>::empty() const noexcept
{
    return (pRoot == nullptr);
}

// -------------------
// node inline methods
// -------------------
template <copy_orderable T>
inline shared_ptr<typename tree<T>::node> tree<T>::node::left() const
{
    return pLeft;
}

template <copy_orderable T>
inline shared_ptr<typename tree<T>::node> tree<T>::node::right() const
{
    return pRight;
}

template <copy_orderable T>
inline shared_ptr<typename tree<T>::node> tree<T>::node::up() const
{
    return pParent->lock();
}

template <copy_orderable T>
inline const T& tree<T>::node::item() const
{
    return myItem;
}

// ostream& operator << (ostream& os, node::child_t child);
// ostream& operator << (ostream& os, node::color_t color);

// ---------------------------
// STL template specifications
// ---------------------------

// swap()
// other algorithms?

#endif
