
#include "tree.hpp"

#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::clog;
using std::cerr;
using std::endl;

/// @brief The main function.
/// @return 0 if all goes well.
int main()
{

    // Set up log file; if successful, then attach it to clog.
    std::ofstream logFile("tree_log.txt");

    if (logFile.is_open())
        clog.tie(&logFile);
    else
        cerr << "unable to tie tree_log.txt to clog" << std::endl;

    clog << "test data" << endl;

    // Initialize tree.
    tree<int> tree;

    tree.insert(1); // root
    tree.insert(6); // root->right
    tree.insert(4); // root->right->left -- rotate right at 6, left at 1
    tree.insert(5); // root->right->left -- no rotation
    tree.insert(19); // root->right->right -- no rotation
    tree.insert(13); // root->right->right->left -- chain of rotations

    // tree should look close to this, but more rotations to rebalance:
    //     4
    // 1       6
    //       5   19
    //          13

    // I think this is the rebalance after 13's insertion?

    //       6
    //    4    19 
    //  1   5 13 


    tree.erase(6);

    return 0;
}