#include "tree.hpp"

// ------------------------
// tree<T>::tree definition
// ------------------------

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
    auto pNewNode = std::make_shared<node>(item);

    // TODO: insertion logic here
    // bst_insert(item)
    pNewNode->set_color(color_t::red);
    // TODO: should the balance take place in tree<T> or node<T>?
    // I'm thinking the nodes should be the balancers.
    // pNewNode->balance();

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
        T& thisItem = pCurrent->item();

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
