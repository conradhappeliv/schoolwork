#include "avltreeindex.h"
#include <iostream>

// cpmstructpr
AVLTreeIndex::AVLTreeIndex()
{
    root = NULL;
}

// destructor
AVLTreeIndex::~AVLTreeIndex()
{
    clear(root);
}

// used by destructor to recursively delete nall nodes in tree
void AVLTreeIndex::clear(AVLTreeNode *n)
{
    if (n != NULL)
    {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert new node into tree
void AVLTreeIndex::insert(AVLTreeNode *newNode)
{
    AVLTreeNode *temp, *prev, *parent;

    temp = root; // current node
    prev = NULL; // previous node traversed
    parent = NULL; // parent node to current node

    // case: tree is empty
    if (root == NULL)
    {
        root = newNode;
        return;
    }

    // case: tree is not empty, traverse for location to insert till temp reaches end
    while (temp != NULL)
    {
        prev = temp;
        if (temp->balance != balanced) parent = temp;
        if (newNode->key < temp->key) temp = temp->left;
        else temp = temp->right;
    }

    newNode->parent = prev; // set parent
    if (newNode->key < prev->key) prev->left = newNode; // insert left
    else prev->right = newNode; // insert right

    restoreBalance(parent, newNode); // restores balance of AVL tree
}

void AVLTreeIndex::restoreBalance(AVLTreeNode *parent, AVLTreeNode *newNode)
{
    // case 1: parent is balanced, newNode unbalances
    if (parent == NULL)
    {
        if (newNode->key < root->key) root->balance = biasleft; // newNode inserted left of root
        else root->balance = biasright; // newNode inserted right of root
        adjustBalance(root, newNode);
    }

    // case 2: insertion of newNode in opposite subtree of parent's current balance
    else if (((parent->balance == biasleft) && (newNode->key > parent->key)) ||
             ((parent->balance == biasright) && (newNode->key < parent->key)))
    {
        parent->balance = balanced;
        adjustBalance(parent, newNode);
    }

    // case 3: insertion of newNode in right child of parent
    else if (parent->balance == biasright)
    {
        // insertion into right subtree of right child
        if (newNode->key > parent->right->key) // single rotation left
        {
            parent->balance = balanced;
            rotateLeft(parent);
            adjustBalance(parent->parent, newNode);
        }
        // insertion into left subtree of right child
        else if (newNode->key < parent->right->key) // double rotation left
        {
            rotateRight(parent->right);
            rotateLeft(parent);
            adjustRL(parent, newNode);
        }
    }

    // case 4: insertion of newNode in left child of parent
    else if (parent->balance == biasleft)
    {
        // insertion into left subtree of left child
        if (newNode->key < parent->left->key) // single rotation right
        {
            parent->balance = balanced;
            rotateRight(parent);
            adjustBalance(parent->parent, newNode);
        }
        // insertion into right subtree of left child
        else if (newNode->key < parent->right->key) // double rotation right
        {
            rotateLeft(parent->left);
            rotateRight(parent);
            adjustLR(parent, newNode);
        }
    }
}

// adjust balance for a single rotation
void AVLTreeIndex::adjustBalance(AVLTreeNode *last, AVLTreeNode *first)
{
    AVLTreeNode *temp = first->parent;
    while (temp != last)
    {
        if (first->key < temp->key) temp->balance = biasleft;
        else temp->balance = biasright;
        temp = temp->parent;
    }
}

// single rotate left
void AVLTreeIndex::rotateLeft(AVLTreeNode *n)
{
    AVLTreeNode *temp = n->right; // point to n's right child
    n->right = temp->left; // temp's left child = n's right child
    if (temp->left != NULL) temp->left->parent = n; // if left child exists, reset parent
    if (n->parent == NULL) // if n is root
    {
        root = temp;
        temp->parent = NULL;
    }
    else if (n->parent->left == n) n->parent->left = temp; // if n is left child of parent, temp is new left child
    else n->parent->right = temp; // if n is right child of parent, temp is new right child

    temp->left = n; // n is left child of temp
    n->parent = temp; // reset n's parent to temp
}

// single rotate right
void AVLTreeIndex::rotateRight(AVLTreeNode *n)
{
    AVLTreeNode *temp = n->left; // point to n's left child
    n->left = temp->right; // temp's right child = n's left child
    if (temp->right!= NULL) temp->right->parent = n; // if right child exists, reset parent
    if (n->parent == NULL) // if n is root
    {
        root = temp;
        temp->parent = NULL;
    }
    else if (n->parent->left == n) n->parent->left = temp; // if n is left child of parent, temp is new left child
    else n->parent->right = temp; // if n is right child of parent, temp is new right child

    temp->right = n; // n is right child of temp
    n->parent = temp; // reset n's parent to temp
}

// adjust balance for a double rotate right
void AVLTreeIndex::adjustLR(AVLTreeNode *last, AVLTreeNode *first)
{
    if (last == root) last->balance = balanced;
    else if (first->key < last->parent->key)
    {
        last->balance = biasright;
        adjustBalance(last->parent->left, first);
    }
    else
    {
        last->balance = balanced;
        last->parent->left->balance = biasleft;
        adjustBalance(last, first);
    }
}

// adjust balance for a double rotate left
void AVLTreeIndex::adjustRL(AVLTreeNode *last, AVLTreeNode *first)
{
    if (last == root) last->balance = balanced;
    else if (first->key > last->parent->key)
    {
        last->balance = biasleft;
        adjustBalance(last->parent->right, first);
    }
    else
    {
        last->balance = balanced;
        last->parent->right->balance = biasright;
        adjustBalance(last, first);
    }
}

// print tree
void AVLTreeIndex::printTree()
{
    std::cout << "\n*****Printing AVL tree*****\n";
    std::cout << "Root node: " << root->key << "\n";
    std::cout << "Balance factor: " << root->balance << "\n\n";
    print(root);
}

void AVLTreeIndex::print(AVLTreeNode *n)
{
    if (n != NULL)
    {
        std::cout << "Node" << n->key << "\n";
        std::cout << "Balance factor: " << n->balance << "\n\n";

        // print left subtree
        if (n->left != NULL)
        {
            std::cout << "***left child***\n";
            print(n->left);
            std::cout << "returning to node " << n->key << " from left subtree\n";
        }
        else std::cout << "***left subtree is empty\n";

        // print right subtree
        if (n->right != NULL)
        {
            std::cout << "***right child***\n";
            print(n->right);
            std::cout << "returning to node " << n->key << " from right subtree\n";
        }
        else std::cout << "***right subtree is empty\n";
    }
}
