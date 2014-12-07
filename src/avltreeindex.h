// Owner: Edward Li

#ifndef AVLTREEINDEX_H
#define AVLTREEINDEX_H

#include <string>
#include "index.h"

const int biasleft = -1;
const int balanced = 0;
const int biasright = 1;
enum printPath {LEFT, KEY, RIGHT};

struct AVLTreeNode : public Index {
    std::string key;
    entry nodeentry;
    AVLTreeNode* left;
    AVLTreeNode* right;
    AVLTreeNode* parent;
    int balance;
};

class AVLTreeIndex : public Index
{
public:
    AVLTreeIndex(std::string);
    ~AVLTreeIndex();
    virtual void add(const unsigned int, const std::string, const unsigned int);
    virtual void save();
    virtual void load();
    virtual void clear();
    virtual void find(std::string);
    virtual std::map<unsigned int, unsigned int> findAll(std::string);

private:
    AVLTreeNode* search(std::string compkey);
    void insert(AVLTreeNode *n);
    void restoreBalance(AVLTreeNode *parent, AVLTreeNode *newNode);
    void adjustBalance(AVLTreeNode *last, AVLTreeNode *first);
    void rotateLeft(AVLTreeNode *n);
    void rotateRight(AVLTreeNode *n);
    void adjustLR(AVLTreeNode *last, AVLTreeNode *first);
    void adjustRL(AVLTreeNode *last, AVLTreeNode *first);

    void dumpTree(std::ofstream& fout, const AVLTreeNode* node);
    void print(std::ofstream& fout, printPath dir, const AVLTreeNode* node);

    AVLTreeNode *root;
    void purge(AVLTreeNode *n);
    void addEntry (const entry e);
};

#endif // AVLTREEINDEX_H
