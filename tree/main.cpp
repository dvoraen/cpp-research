#include "tree.hpp"


/// @brief The main function.
/// @return 0 if all goes well.
int main()
{
    // Initialize tree.
    tree<int> tree;

    tree.insert(1); // root
    tree.insert(6); // root->right
    tree.insert(4); // root->right->left -- rotate right at 6, left at 1
    tree.insert(5); // root->right->left -- no rotation
    tree.insert(19); // root->right->right -- no rotation
    tree.insert(13); // root->right->right->left -- chain of rotations

    // tree before rotations
    //       1
    //  *         6
    //         4    19
    //        * 5  13 *
    //

    // I think this is the rebalance after 13's insertion?
    //       6
    //    4    19 
    //  1   5 13 *

    tree.report();

    tree.clear();
    tree.report();

    // tree.remove(6);
    // tree.report();

    return 0;
}