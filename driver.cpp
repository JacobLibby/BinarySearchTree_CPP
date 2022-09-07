/*    SECTION: COMP 116 - Data Structures
 * ASSIGNMENT: Project 8 - The Binary Search Tree.cpp
 *       DATE: 6 December 2019
 *   DUE DATE: 6 December 2019
 *
 *    SUMMARY: This class allows the user to create and manipulate a BST (Binary Search Tree). Numerous
 *              functions are coded into the program, with catches in case of user error.
 *
 *   COMMENTS: Although the descriptor did not explicitly prohibit me from editing the given code, I would
 *              have most likely changed the print function for the vector in order for it to not print an
 *              extra comma, by using an if statement to see if it was empty, and then printing the first
 *              item, and then in a for loop, printing a comma followed by the next item. In addition, I was
 *              uncertain if removing the comments in the header file would have caused a deduction in points,
 *              so I decided to erring on the side of caution by not removing them from BST.h. This code was quite
 *              difficult to wrap my head around at points (recursion is a topic that I look forward to learning
 *              about in the future) but am very proud of my final product.
 *
 * PROGRAMMER: Jacob Libby
 *             I have abided by the Wheaton Honor Code
 */

#include <iostream>
#include "BST.h"

using namespace std;

void print(vector<int> v) {
    cout << "vec: ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ", ";
    }
    cout << endl;
}

int main() {

    // using default constructor to create BST
    BST tree;
    cout << "getHeight(): " << tree.getHeight() << endl;
    cout << "isBalanced(): " << tree.isBalanced() << endl << endl;

    // inserting nodes
    cout << "getHeight(): " << tree.getHeight() << endl;
    cout << "isBalanced(): " << tree.isBalanced() << endl;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(2);
    tree.insert(12);
    tree.insert(11);
    tree.insert(14);
    cout << "getHeight(): " << tree.getHeight() << endl;
    cout << "isBalanced(): " << tree.isBalanced() << endl << endl;

    // testing traversals
    vector<int> v1 = tree.preOrder();
    print(v1);
    vector<int> v2 = tree.inOrder();
    print(v2);
    vector<int> v3 = tree.postOrder();
    print(v3);
    vector<int> v4 = tree.levelOrder();
    print(v4);
    vector<int> v5 = tree.inOrderNonRecursive();
    print(v5);
    vector<int> v6 = tree.postOrderNonRecursive();
    print(v6);
    v4 = tree.levelOrder();
    print(v4);

    // testing remove
    tree.remove(14);
    tree.remove(15);
    cout << "getHeight(): " << tree.getHeight() << endl;
    cout << "isBalanced(): " << tree.isBalanced() << endl;

    // testing find
    cout << "Node of value 10 found at memory location: " << tree.find(10) << endl;
    cout << "Node of value 2 found at memory location: " << tree.find(2) << endl;

    return 0;
}