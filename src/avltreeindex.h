// Owner: Edward Li

#ifndef AVLTREEINDEX_H
#define AVLTREEINDEX_H
#include <string>

const int biasleft = -1;
const int balanced = 0;
const int biasright = 1;

struct AVLTreeNode
{
    std::string key;
    // struct entry;
    AVLTreeNode *left;
    AVLTreeNode *right;
    AVLTreeNode *parent;
    int balance;
};

class AVLTreeIndex
{
private:
    AVLTreeNode *root;
    void clear(AVLTreeNode *n);
    void print(AVLTreeNode *n);
    AVLTreeNode* find(std::string keyword); // TODO: to be implemented

public:
    AVLTreeIndex();
    ~AVLTreeIndex();

    void insert(AVLTreeNode *n);
    void restoreBalance(AVLTreeNode *parent, AVLTreeNode *newNode);
    void adjustBalance(AVLTreeNode *last, AVLTreeNode *first);
    void rotateLeft(AVLTreeNode *n);
    void rotateRight(AVLTreeNode *n);
    void adjustLR(AVLTreeNode *last, AVLTreeNode *first);
    void adjustRL(AVLTreeNode *last, AVLTreeNode *first);
    void printTree();
};

#endif // AVLTREEINDEX_H
