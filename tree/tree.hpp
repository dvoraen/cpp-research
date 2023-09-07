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

// ------------------
// tree<T> definition
// ------------------

template <copy_orderable T>
tree<T>::tree() : pRoot(nullptr), mySize(0)
{
}

template <copy_orderable T>
tree<T>::tree(const tree<T>& tree) : tree()
{
    // iterate through tree and this->insert() it all

    // this->insert(tree.begin(), tree.end());
}

template<copy_orderable T>
tree<T>::tree(tree<T>&& tree) noexcept : pRoot(tree.pRoot), mySize(tree.mySize)
{
    tree.pRoot.reset();
    tree.mySize = 0;
}

template<copy_orderable T>
tree<T>::~tree()
{
    // TODO: evaluate need to destroy nodes
    // smart pointers should be able to handle it?
}

// Insert an item of type T.
template<copy_orderable T>
void tree<T>::insert(const T& item)
{
    using color_t = typename node<T>::color_t;
    using child_t = typename node<T>::child_t;

    auto pNewNode = std::make_shared<node<T>>(item);

    // TODO: insertion logic here
    // bst_insert(item);
    pNewNode->set_color(color_t::red);
    // TODO: should the balance take place in tree<T> or node<T>?
    // this->balance_at(pNewNode);

    pNewNode->set_child(child_t::left, pRoot);
    pRoot = pNewNode;

    this->mySize += 1;
}

template <copy_orderable T>
void tree<T>::erase(const T& item)
{
    if (this->empty() || !this->contains(item))
        return;

    // TODO: deletion logic here

    this->mySize -= 1;
}

template<copy_orderable T>
void tree<T>::clear() noexcept
{
    pRoot.reset();

    this->mySize = 0;
}

template <copy_orderable T>
bool tree<T>::contains(const T& item) const
{
    if (this->empty())
        return false;

    return (this->find(item) ? true : false);
}

template <copy_orderable T>
const shared_ptr<node<T>> tree<T>::find(const T& item) const
{
    auto pCurrent = pRoot;

    while (pCurrent)
    {
        const T& thisItem = pCurrent->item();

        if (item == thisItem)
            return pCurrent;
        else if (item < thisItem)
            pCurrent = pCurrent->left();
        else
            pCurrent = pCurrent->right();
    }

    return nullptr;
}

template<copy_orderable T>
void tree<T>::balance_at(node<T>& node)
{
}

// ---------------------------
// STL template specifications
// ---------------------------

// swap()
// other algorithms?

#endif
