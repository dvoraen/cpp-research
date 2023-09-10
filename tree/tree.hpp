// tree.hpp
// Ian Haley

// Templatized, STL-compatible, self-balancing binary search tree

#pragma once

#ifndef __tree_hpp__
#define __tree_hpp__

// TODO: Audit changes to weak_ptr<node>
// TODO: Replace remaining node* uses with weak_ptr<node>

#include "node.hpp"
#include "concepts.hpp"

#include <memory>

using std::shared_ptr;
using std::weak_ptr;
using std::unique_ptr;

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;

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

    void remove(const T& item);
    void clear() noexcept;

    bool contains(const T& item) const;

    size_t size() const noexcept;
    bool empty() const noexcept;

    // TODO: report() will spill the guts on the tree using in-order traversion
    void report() const;

private:
    shared_ptr<node<T>> pRoot; // root of tree    
    size_t mySize; // size of tree

    void insert_node(shared_ptr<node<T>> pNewNode);

    void report_recurse(const shared_ptr<node<T>>& pNode) const;
    void visit_node(const shared_ptr<node<T>>& pNode) const;

    const shared_ptr<node<T>> find(const T& item) const;
    void balance_at(shared_ptr<node<T>> node);
};

// ------------------
// tree<T> definition
// ------------------

template <copy_orderable T>
tree<T>::tree() : pRoot{ nullptr }, mySize{ 0 }
{
}

template <copy_orderable T>
tree<T>::tree(const tree<T>& tree) : tree()
{
    // iterate through tree and this->insert() it all

    // this->insert(tree.begin(), tree.end());
}

template<copy_orderable T>
tree<T>::tree(tree<T>&& tree) noexcept : pRoot{ tree.pRoot }, mySize{ tree.mySize }
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
    shared_ptr<node<T>> pNewNode{ std::make_shared<node<T>>(item) };

    this->insert_node(pNewNode);
    this->balance_at(pNewNode);

    this->mySize += 1;
}

template <copy_orderable T>
void tree<T>::remove(const T& item)
{
    if (this->empty() || !this->contains(item))
        return;

    // TODO: deletion logic here

    // this->balance_at();

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
inline size_t tree<T>::size() const noexcept
{
    return mySize;
}

template <copy_orderable T>
inline bool tree<T>::empty() const noexcept
{
    return (pRoot == nullptr);
}

template<copy_orderable T>
void tree<T>::report() const
{
    if (this->empty())
    {
        cout << "tree is empty" << endl;
        return;
    }

    report_recurse(pRoot);
}

// tree<T> private methods

template<copy_orderable T>
void tree<T>::insert_node(shared_ptr<node<T>> pNewNode)
{
    // CASE: empty tree; insert at root
    if (!pRoot)
    {
        pRoot = pNewNode;
        return;
    }

    using child_t = typename node<T>::child_t;
    child_t whichChild{};

    shared_ptr<node<T>> pCurrentNode{ pRoot };
    shared_ptr<node<T>> pParentNode{ nullptr };

    // Iterate through tree to find insertion point.
    while (pCurrentNode)
    {
        // Track parent node.
        pParentNode = pCurrentNode;

        // If left child, track that we're going left.
        if (pNewNode->get_item() < pCurrentNode->get_item())
        {
            pCurrentNode = pCurrentNode->left();
            whichChild = child_t::left;
        }
        // If right child, track that we're going right.
        else
        {
            pCurrentNode = pCurrentNode->right();
            whichChild = child_t::right;
        }
    }

    // Parent will set the child of the direction we last went.
    // Operation is done relative to the parent to ensure we get the right
    // smart pointer pointing to the right node (the new one).
    pParentNode->set_child(whichChild, pNewNode);
    pNewNode->set_parent(pParentNode);
}

template<copy_orderable T>
void tree<T>::report_recurse(const shared_ptr<node<T>>& pNode) const
{
    if (!pNode)
        return;

    visit_node(pNode);
    report_recurse(pNode->left());
    report_recurse(pNode->right());
}

template<copy_orderable T>
void tree<T>::visit_node(const shared_ptr<node<T>>& pNode) const
{
    pNode->status();
}

template <copy_orderable T>
const shared_ptr<node<T>> tree<T>::find(const T& item) const
{
    shared_ptr<node<T>> pCurrent{ pRoot };

    while (pCurrent)
    {
        const T& thisItem{ pCurrent->get_item() };

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
void tree<T>::balance_at(shared_ptr<node<T>> node)
{
    // CASE: rotating the tree root
}

#endif
