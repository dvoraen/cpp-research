// tree.hpp
// Ian Haley

// Templatized, STL-compatible, self-balancing binary search tree

// TODO: concepts for T?

#pragma once

#ifndef __tree_hpp__
#define __tree_hpp__

#include <memory>

using std::shared_ptr;
using std::weak_ptr;
using std::unique_ptr;

// TODO: Audit changes to weak_ptr<node>
// TODO: Replace remaining node* uses with weak_ptr<node>

#include "node.hpp"
#include "concepts.hpp"


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
    shared_ptr<node<T>> pRoot; // root of tree    
    size_t mySize; // size of tree

    const shared_ptr<node<T>> find(const T& item) const;
    void balance_at(node<T>& node);
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

// ---------------------------
// STL template specifications
// ---------------------------

// swap()
// other algorithms?

#endif
