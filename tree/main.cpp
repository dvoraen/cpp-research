
#include "tree.hpp"

#include <iostream>
#include <vector>

int main()
{
    using std::cout;
    using std::endl;

    tree<int> tree;

    tree.insert(1); // root
    tree.insert(6); // root->right
    tree.insert(4); // root->right->left -- rotate right at 6, left at 4
    tree.insert(5); // root->right->left -- no rotation
    tree.insert(19); // root->right->right -- no rotation
    tree.insert(13); // root->right->right->left -- rotate?

    return 0;
}