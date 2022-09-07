#ifndef BST_BST_H
#define BST_BST_H

#include <vector>
#include "BSTNode.h"
using std::vector;

class BST {
public:
    BST();
    ~BST();

    bool isEmpty() const;
    int getSize() const;

    // find returns the BSTNode* with a given target key
    BSTNode* find (int key);

    // make sure to cover different scenarios and use
    // private helper functions for recursive approaches
    // 1. empty tree
    // 2. a tree with only one node (root)
    // 3. insert/remove a leaf node
    // 4. insert/remove a branch node
    void insert(int key);
    void remove(int key);

    // contain checks if a BSTNode contains the target key
    bool contain(int key);
    // returns the height of a tree/subtree
    int getHeight() const;

    // For every node in the tree, the difference between heights of its left
    // subtree and its right subtree is no more than 1, then it is considered
    // as a balanced tree.
    bool isBalanced();

    // public interface for traversals
    vector<int> preOrder();
    vector<int> inOrder();
    vector<int> inOrderNonRecursive();
    vector<int> postOrder();
    vector<int> postOrderNonRecursive();
    vector<int> levelOrder();

private:
    BSTNode *root;
    int size;

    /**
     * helper function for insert
     * @param key the key to insert in the tree
     * @param current the root of the tree in which we are currently inserting the new key
     * @return the root of a tree that is just like current, but with the new key inserted
     */
    BSTNode* insert_h(int key, BSTNode *newNode);

    /**
     * helper function used by find, update and contain
     * @param key the key we are looking for in the tree
     * @param current the root of the tree in which we are currently searching for the key
     * @return a pointer to the BSTNode that contains the key, nullptr if the key is not in the tree
     */
    BSTNode* find_h(int key, BSTNode* current);

    /**
     * helper function for remove
     * @param key the key to be removed from the tree
     * @param current the root of the tree in which we are currently removing the key
     * @return a pointer to a BSTNode that is the root of a tree just like current, but with key removed
     * @throws runtime_error if key is not in the tree
     */
    BSTNode* remove_h(int key, BSTNode* current);

    /**
     * getMax finds the node containing the maximal key in the tree
     * @param current the root of the tree in which we are searching
     * @return a pointer to the BSTNode containing the maximal key
     * @throws runtime_error if current is an empty tree
     */
    BSTNode* getMax(BSTNode* current);

    /* helper functions for the traversals */
    void preOrder_h(BSTNode* current, vector<int>& v);
    void inOrder_h(BSTNode* current, vector<int>& v);
    void postOrder_h(BSTNode* current, vector<int>& v);
    void postOrderNonRecursive_h(BSTNode* current, vector<int>& v);
    bool isInVector(vector<int> vector, int key);
    void levelOrder_h(BSTNode *curr, vector<int>& v);
    void inOrderNonRecursive_h(BSTNode* curr, vector<int>& v);
    void destructTree(BSTNode* current);
    bool isBalanced_h(BSTNode *current);
    int getHeight_h(BSTNode* current) const;
};


#endif //BST_BST_H
