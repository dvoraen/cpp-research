#include "tree.hpp"

#include <iostream>
using std::clog;
using std::endl;

using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;

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
    pNewNode->pParent = pRoot;

    pRoot = pNewNode;

    this->mySize += 1;
}

template <copy_orderable T>
void tree<T>::erase(const T& item)
{
    if (this->empty() || !this->contains(item))
        return;

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
    else
    {
        auto pResult = this->find(item);
        if (pResult.get() != nullptr)
            return false;
        else
            return true;
    }
}

template <copy_orderable T>
const shared_ptr<typename tree<T>::node> tree<T>::find(const T& item) const
{
    auto pCurrent = pRoot;

    while (pCurrent.get() != nullptr)
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

// ---------------------
// tree::node definition
// ---------------------

template<copy_orderable T>
tree<T>::node::node() : pParent(nullptr), pLeft(nullptr), pRight(nullptr), myColor(color_t::black)
{
}

template<copy_orderable T>
tree<T>::node::node(const T& item) : node(), myItem(item)
{
}

template<copy_orderable T>
tree<T>::node::node(T&& item) : node(), myItem(item)
{
}

template<copy_orderable T>
tree<T>::node::~node()
{
    clog << "~node() -> " << this->myItem << endl;
    clog << "- left is " << (pLeft ? pLeft->myItem : "null") << endl;
    clog << "- right is " << (pRight ? pRight->myItem : "null") << endl;
}

template <copy_orderable T>
void tree<T>::node::set_child(child_t child, shared_ptr<node> pNewChild)
{
    shared_ptr<node>& pChild{ (child == child_t::left) ? pLeft : pRight };

    pChild = pNewChild;
}

template <copy_orderable T>
void tree<T>::node::set_color(color_t color)
{
    myColor = color;

    clog << "node (" << myItem << ") is now ";
    clog << (myColor == color_t::black ? "black" : "red");
    clog << endl;
}

template <copy_orderable T>
void tree<T>::node::rotate_left()
{
    clog << "rotate_left() at " << myItem << endl;
}

template <copy_orderable T>
void tree<T>::node::rotate_right()
{
    clog << "rotate_right() at " << myItem << endl;
}

template <copy_orderable T>
shared_ptr<typename tree<T>::node> tree<T>::node::sibling() const
{
    if (!pParent)
        return nullptr;

    shared_ptr<node> pParentNode = pParent->lock();

    // if this is parent's left child; return right child
    // BUG: this ptr won't be equal to a shared_ptr, necessarily
    if (this == pParentNode->left())
        return pParentNode->right();
    else
        return pParentNode->left();
}

template <copy_orderable T>
shared_ptr<typename tree<T>::node> tree<T>::node::uncle() const
{
    return (pParent ? pParent->lock()->sibling() : nullptr);
}

template <copy_orderable T>
shared_ptr<typename tree<T>::node> tree<T>::node::successor() const
{
    if (!this->right())
        return nullptr;

    // successor is the left-most node of the right subtree
    auto pCurrent = this->right();

    while (pCurrent->left())
        pCurrent = pCurrent->left();

    clog << "successor of " << this->myItem << " is " << pCurrent->myItem << endl;

    return pCurrent;
}

// ---------------------------
// STL template specifications
// ---------------------------
