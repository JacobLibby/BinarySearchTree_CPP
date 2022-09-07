#include "BST.h"
#include "BSTNode.h"
#include <vector>
#include <queue>
#include <stack>
#include <stdexcept>

using namespace std;

BST::BST() {
    this->root = nullptr;
    this->size = 0;
}

BST::~BST() {
    this->destructTree(this->root);
}

bool BST::isEmpty() const {
    return this->size == 0;
}

int BST::getSize() const {
    return this->size;
}

void BST::insert(int key) {
    if (this->isEmpty()){
        this->root = new BSTNode(key, nullptr, nullptr);
    }
    else { // BST was not empty
        BSTNode *curr = this->root;
            insert_h(key, curr);
    }
    this->size++;
}

BSTNode* BST::find(int key) {
    BSTNode* location = find_h(key, this->root);
    if (location == nullptr) {
        throw runtime_error("BST::find, key not present in BST");
    }
    return location;
}

void BST::remove(int key) {
    this->root = this->remove_h(key, this->root);
}

bool BST::contain(int key) {
    BSTNode* location = find_h(key, this->root);
    return location != nullptr;
}

int BST::getHeight() const{
    int maxHeight = getHeight_h(this->root);
    if (maxHeight == 0){
        return maxHeight;
    }
    return maxHeight - 1;
}

int BST::getHeight_h(BSTNode *current) const {
    if (current == nullptr){
        return 0;
    }
    if (this->root->left == nullptr && this->root->right == nullptr){
        return 0;
    }
    int lHeight = getHeight_h(current->left) + 1; // increase height
    int rHeight = getHeight_h(current->right) + 1; // increase height
    return max(lHeight, rHeight);
}

vector<int> BST::preOrder() {
    vector<int> vals;
    this->preOrder_h(this->root, vals);
    return vals;
}

vector<int> BST::inOrder() {
    vector<int> vals;
    this->inOrder_h(this->root, vals);
    return vals;
}

vector<int> BST::inOrderNonRecursive(){
    vector<int> v;
    inOrderNonRecursive_h(this->root, v);
    return v;
}

void BST::inOrderNonRecursive_h(BSTNode* curr, vector<int>& v){
    stack<BSTNode> nodeStack;
    if (curr->right != nullptr) {
        nodeStack.push(curr->key);
        curr = curr->right;
        while (curr != this->root) {
            if (curr->key == nodeStack.top().key) {
                curr = curr->left;
                v.push_back(nodeStack.top().key);
                nodeStack.pop();
            }
            if (curr->right != nullptr) {
                nodeStack.push(curr->key);
                curr = curr->right;
            } else {
                v.push_back(curr->key);
                if (curr->left != nullptr) {
                    curr = curr->left;
                } else {
                    curr = find(nodeStack.top().key);
                }
            }
        }
    }
    if (curr->left != nullptr){
        v.push_back(curr->key);
        nodeStack.push(curr->key);
        curr = this->root->left;
        while (curr != this->root) {
            if (curr->key == nodeStack.top().key){
                curr = curr->left;
                v.push_back(nodeStack.top().key);
                nodeStack.pop();
            }
            if (curr->right != nullptr) {
                nodeStack.push(curr->key);
                curr = curr->right;
            } else {
                v.push_back(curr->key);
                if (curr->left != nullptr) {
                    curr = curr->left;
                } else {
                    curr = find(nodeStack.top().key);
                }
            }
        }
    }

    // flip vector to correct order
    stack<int> flipper;
    int size = v.size();
    for (int i = 0; i < size; i++){
        flipper.push(v[0]);
        v.erase(v.begin());
    }
    for (int i = 0; i < size; i++){
        v.push_back(flipper.top());
        flipper.pop();
    }
}

vector<int> BST::postOrder() {
    vector<int> vals;
    this->postOrder_h(this->root, vals);
    return vals;
}

vector<int> BST::postOrderNonRecursive() {
    vector<int> v;
    postOrderNonRecursive_h(this->root, v);
    return v;
}

void BST::postOrderNonRecursive_h(BSTNode *current, vector<int> &v) {
    stack<BSTNode> nodeStack;

    if (this->root != nullptr) { // BST is not empty
        // traversing left side of root
        current = this->root->left;
        nodeStack.push(this->root->key);
        while (current != this->root) {
            if (nodeStack.top().key == current->key &&
            (current->right == nullptr || isInVector(v, current->right->key))) {
                v.push_back(current->key);
                nodeStack.pop();
                current = find(nodeStack.top().key);
            } else if (current->left != nullptr && !isInVector(v, current->left->key)) {
                nodeStack.push(current->key);
                current = current->left;
            }
            else if (current->left == nullptr && current->right != nullptr) {
                nodeStack.push(current->key);
                current = current->right;
            } else if (current->left == nullptr && current->right == nullptr) {
                v.push_back(current->key);
                current = find(nodeStack.top().key);
            }
        }

        // traversing side of root
        current = this->root->right;
        while (current != this->root) {
            if (nodeStack.top().key == current->key &&
            (current->right == nullptr || isInVector(v, current->right->key))) {
                v.push_back(current->key);
                nodeStack.pop();
                current = find(nodeStack.top().key);
            } else if (current->left != nullptr && !isInVector(v, current->left->key)) {
                nodeStack.push(current->key);
                current = current->left;
            }
            else if (current->left == nullptr && current->right != nullptr) {
                nodeStack.push(current->key);
                current = current->right;
            } else if (current->left == nullptr && current->right == nullptr) {
                v.push_back(current->key);
                current = find(nodeStack.top().key);
            } else if ((current->left == nullptr || isInVector(v, current->left->key)) && current->right != nullptr){
                current = current->right;
                if (current->right != nullptr){
                    nodeStack.push(current->key);
                }
            }
        }
        v.push_back(this->root->key);
    }
}

bool BST::isInVector(vector<int> vector, int key){ // check if node is already added to vector
    for (int i = 0; i < vector.size(); i++){
        if (vector[i] == key){
            return true;
        }
    }
    return false;
}

vector<int> BST::levelOrder(){
    BSTNode *curr = this->root;
    vector<int> vals;
    levelOrder_h(curr, vals);
    return vals;
}

void BST::levelOrder_h(BSTNode *curr, vector<int> &v) { ////////need getHeight!!!
    queue<BSTNode> levelOrderQueue;
    if (curr == nullptr) {
        return;
    }
    levelOrderQueue.push(*curr);
    while (!levelOrderQueue.empty()) {
        v.push_back(levelOrderQueue.front().key);///right func???
        curr = find(levelOrderQueue.front().key);
        if (levelOrderQueue.front().left != nullptr) {

            levelOrderQueue.push(*curr->left);
        }
        if (levelOrderQueue.front().right != nullptr) {
            levelOrderQueue.push(*curr->right);
        }
        levelOrderQueue.pop();
    }
}

// Helper functions
BSTNode* BST::insert_h(int key, BSTNode *curr) {
    BSTNode *prev = curr;

    while (curr != nullptr) {
        if (key < curr->key) {
            prev = curr;
            curr = curr->left;
        } else if (key > curr->key) {
            prev = curr;
            curr = curr->right;
        } else { // key == curr->key
            throw runtime_error("BST::insert_h, duplicate key already exists in the BST");
        }
    }
    if (key > prev->key) {
        prev->right = new BSTNode(key, nullptr, nullptr);
    } else if (key < prev->key) {
        prev->left = new BSTNode(key, nullptr, nullptr);
    }
}

BSTNode* BST::find_h(int key, BSTNode *curr) {
    while (curr != nullptr && curr->key != key){
        if (key < curr->key) {
            curr = curr->left;
        } else if (key > curr->key) {
            curr = curr->right;
        }
    }
    return curr;
}

BSTNode* BST::remove_h(int key, BSTNode *curr) {
    if (this->root == nullptr){ // BST is empty
        throw runtime_error("BST::remove_h, BST empty; remove key not found");
    } else {
        BSTNode* prev = curr;
        while (curr != nullptr){
            if (key > curr->key){
                prev = curr;
                curr = curr->right;
            } else if (key < curr->key){
                prev = curr;
                curr = curr->left;
            } else if (key == curr->key){ // key found

                // KEY IS A LEAF
                if (curr->left == nullptr && curr->right == nullptr){
                    if (key < prev->key){ // prev->left == key
                        prev->left = nullptr;
                    } else if (key > prev->key){ // prev->right == key
                        prev->right = nullptr;
                    } else { // key == prev->key ... key == this->root
                        this->root = nullptr;
                    }
                }

                // KEY IS A BRANCH
                else { // key is a branch node
                    BSTNode *leftCurr = curr->left; BSTNode *rightCurr = curr->right;
                    if (leftCurr == nullptr){
                        if (key > prev->key){
                            prev->right = prev->right->right;
                        } else if (key < prev->key){
                            prev->left = prev->left->right;
                        } else { // key == prev->key ... key == root
                            this->root = this->root->right;
                        }
                    } else if (rightCurr == nullptr){
                        if (key > prev->key){
                            prev->right = prev->right->left;
                        } else if (key < prev->key){
                            prev->left = prev->left->left;
                        } else { // key == prev->key ... key == root
                            this->root = this->root->left;
                        }
                    }

                    // key has two children
                    else { // (leftCurr != nullptr && rightCurr != nullptr)
                        BSTNode *leftPrev = leftCurr;
                        while (leftCurr->right != nullptr){
                            leftPrev = leftCurr;
                            leftCurr = leftCurr->right;
                        }
                        if (key > prev->key){
                            prev->right->key = leftCurr->key;
                        } else if (key < prev->key){
                            prev->left->key = leftCurr->key;
                        } else { // key == prev->key
                            this->root->key = leftCurr->key;
                        }

                        // removing the above replacer to the key
                        leftPrev->right = leftCurr->left;
                    }
                }
                curr = nullptr;
            }
        }
        this->size--;
    }
    return this->root;
}

BSTNode* BST::getMax(BSTNode *curr) {
    if (curr == nullptr){
        throw runtime_error("BST::getMax, BST is empty");
    }
    while (curr->right != nullptr){
        curr = curr->right;
    }
    return curr;
}

void BST::preOrder_h(BSTNode *curr, vector<int> &v) {
    if (curr != nullptr) {
        v.push_back(curr->key);
        this->preOrder_h(curr->left, v);
        this->preOrder_h(curr->right, v);
    }
}

void BST::inOrder_h(BSTNode *curr, vector<int> &v) {
    if (curr != nullptr) {
        this->inOrder_h(curr->left, v);
        v.push_back(curr->key);
        this->inOrder_h(curr->right, v);
    }
}

void BST::postOrder_h(BSTNode *curr, vector<int> &v) {
    if (curr != nullptr) {
        this->postOrder_h(curr->left, v);
        this->postOrder_h(curr->right, v);
        v.push_back(curr->key);
    }
}

void BST::destructTree(BSTNode *curr) {
    if (curr != nullptr) {
        destructTree(curr->left);
        destructTree(curr->right);
        delete curr;
    }
}

bool BST::isBalanced(){
    bool treeIsBalanced = isBalanced_h(this->root);
    return treeIsBalanced;
}

bool BST::isBalanced_h(BSTNode *current) {
    if (current == nullptr){
        return true;
    }
    else if (isBalanced_h(current->left) && isBalanced_h(current->left)) {
        if ((abs(getHeight_h(current->left)-getHeight_h(current->right)))<=1){
            return true;
        }
    }
    return false;
}