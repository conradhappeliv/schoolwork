// Owner: Edward Li

#include "avltreeindex.h"

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <linux/limits.h>

// constructor
AVLTreeIndex::AVLTreeIndex(std::string filename):Index(filename)
{
    root = NULL;
    treeSize = 0;
}

// destructor
AVLTreeIndex::~AVLTreeIndex()
{
    purge(root);
}

// used by destructor to recursively delete all nodes in tree
void AVLTreeIndex::purge(AVLTreeNode *n)
{
    if (n != NULL) {
        purge(n->left);
        purge(n->right);
        delete n;
    }
}

// search for node in tree, returns null if term not found
AVLTreeNode* AVLTreeIndex::search(std::string compkey) {
    AVLTreeNode* temp;
    temp = root;
    while (temp) {
        if (temp->key.compare(compkey) < 0) temp = temp->right;
        else if (temp->key.compare(compkey) > 0) temp = temp->left;
        else if (temp->key.compare(compkey) == 0) break;
    }
    return temp;
}

// insert new node into tree
void AVLTreeIndex::insert(AVLTreeNode* newNode)
{
    AVLTreeNode *temp, *prev, *parent;

    temp = root; // current node
    prev = NULL; // previous node traversed
    parent = NULL; // parent node to current node

    // case: tree is empty
    if (root == NULL) {
        root = newNode;
        return;
    }

    // case: tree is not empty, traverse for location to insert till temp reaches end
    while (temp != NULL) {
        prev = temp;
        if (temp->balance != balanced) parent = temp;
        if (temp->key.compare(newNode->key) < 0) temp = temp->right;
        else if (temp->key.compare(newNode->key) > 0) temp = temp->left;
        else if (temp->key.compare(newNode->key) == 0) {
            std::cout << "node already exists" << std::endl;
            break;
        }
    }

    newNode->parent = prev; // set parent
    if (newNode->key.compare(prev->key) < 0) prev->left = newNode; // insert left
    else prev->right = newNode; // insert right

    treeSize++;
    restoreBalance(parent, newNode); // restores balance of AVL tree
}

void AVLTreeIndex::restoreBalance(AVLTreeNode *parent, AVLTreeNode *newNode)
{
    // case 1: parent DNE, root node case, newNode unbalances
    if (parent == NULL) {
        if (newNode->key < root->key) root->balance = biasleft; // newNode inserted left of root
        else root->balance = biasright; // newNode inserted right of root
        adjustBalance(root, newNode);
    }

    // case 2: insertion of newNode in opposite subtree of parent, balances parent
    else if (((parent->balance == biasleft) && (newNode->key.compare(parent->key) > 0)) ||
             ((parent->balance == biasright) && (newNode->key.compare(parent->key) < 0))) {
        parent->balance = balanced;
        adjustBalance(parent, newNode);
    }

    // case 3: insertion of newNode in right child of parent
    else if (parent->balance == biasright) {
        if (newNode->key > parent->right->key) { // insertion into right subtree of right child, single rotation left
            parent->balance = balanced;
            rotateLeft(parent);
            adjustBalance(parent->parent, newNode);
        } else if (newNode->key < parent->right->key) { // insertion into left subtree of right child, double rotation left
            rotateRight(parent->right);
            rotateLeft(parent);
            adjustRL(parent, newNode);
        }
    }

    // case 4: insertion of newNode in left child of parent
    else if (parent->balance == biasleft) {
        if (newNode->key < parent->left->key) { // insertion into left subtree of left child, single rotation right
            parent->balance = balanced;
            rotateRight(parent);
            adjustBalance(parent->parent, newNode);
        } else if (newNode->key < parent->right->key) { // insertion into right subtree of left child, double rotation right
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
    while (temp != last) {
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
    if (n->parent == NULL) { // if n is root
        root = temp;
        temp->parent = NULL;
    } else if (n->parent->left == n) n->parent->left = temp; // if n is left child of parent, temp is new left child
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
    if (n->parent == NULL) { // if n is root
        root = temp;
        temp->parent = NULL;
    } else if (n->parent->left == n) n->parent->left = temp; // if n is left child of parent, temp is new left child
    else n->parent->right = temp; // if n is right child of parent, temp is new right child

    temp->right = n; // n is right child of temp
    n->parent = temp; // reset n's parent to temp
}

// adjust balance for a double rotate right
void AVLTreeIndex::adjustLR(AVLTreeNode *last, AVLTreeNode *first)
{
    if (last == root) last->balance = balanced;
    else if (first->key < last->parent->key) {
        last->balance = biasright;
        adjustBalance(last->parent->left, first);
    } else {
        last->balance = balanced;
        last->parent->left->balance = biasleft;
        adjustBalance(last, first);
    }
}

// adjust balance for a double rotate left
void AVLTreeIndex::adjustRL(AVLTreeNode *last, AVLTreeNode *first)
{
    if (last == root) last->balance = balanced;
    else if (first->key > last->parent->key) {
        last->balance = biasleft;
        adjustBalance(last->parent->right, first);
    } else {
        last->balance = balanced;
        last->parent->right->balance = biasright;
        adjustBalance(last, first);
    }
}

// print tree
void AVLTreeIndex::dumpTree(std::ofstream& fout, const AVLTreeNode* node) {
    if (node == NULL) {
        std::cout << "empty" << std::endl;
    } else { // if non-empty tree
        print(fout, RIGHT, node);
        if (node->right != NULL) dumpTree(fout, node->right);
        print(fout, KEY, node);
        if (node->left != NULL) dumpTree(fout, node->left);
        print(fout, LEFT, node);
    }
}

// print data for current node
void AVLTreeIndex::print(std::ofstream& fout, printPath dir, const AVLTreeNode* node) {
    if (dir == KEY) {
        // format: keyword;idf;id,freq;id,freq;id,freq;
        fout << node->nodeentry.keyword << ";";
        for (auto i = node->nodeentry.documents.begin(); i != node->nodeentry.documents.end(); i++) {
            fout << i->id << ";";
            fout << i->termFreq << ":";
        }
        fout << "\n";
    }
}


// *********INTERFACE FUNCTIONALITY********
void AVLTreeIndex::add(const unsigned int id, const std::string word, const double freq) {
    entry::doc d;
    d.id = id;
    d.termFreq = freq;
    AVLTreeNode* n = search(word);
    entry& e = n->nodeentry;
    if (e.keyword != word) e.keyword = word;
    e.documents.push_back(d);
}

void AVLTreeIndex::save() {
    std::ofstream fout;
    fout.open(filename, std::ios::out | std::ios::app);
    if (!fout.is_open()) {
        std::cout << "Error opening " << filename << std::endl;
        exit(1);
    } else {std::cout << filename << " successfully opened." << std::endl;}

    for(auto it = references.begin(); it != references.end(); it++) {
        if((*it)[0] != '/') {
            (*it).insert(0, "/");
            char c[PATH_MAX];
            getcwd(c, PATH_MAX);
            (*it).insert(0, c);
        }
        fout << *it << std::endl;
    }


    // write out all data to file
    fout << "ENDREFS" << std::endl;
    dumpTree(fout, root);
    std::cout << "index written to file." << std::endl;
    fout.close();
}

void AVLTreeIndex::load() {
    std::ifstream fin;
    fin.open(filename, std::ios::in);
    if (!fin.is_open()) {
        std::cout << "Error opening " << filename << std::endl;
        return;
    } else {std::cout << filename << " successfully opened." << std::endl;}

    // read in index from file
    std::string ref;
    do {
        std::getline(fin, ref);
        if(ref != "ENDREFS") this->addReference(ref);
    } while(ref != "ENDREFS");
    while (!fin.eof()) {
        entry e;
        std::string keyword_in, idf_in, id_in, tf_in;
        std::getline(fin, keyword_in, ';');
        e.keyword = keyword_in;
        //std::cout << keyword_in << ";" << idf_in << ";";

        bool val = true;
        while(val) {
            std::getline(fin, id_in, ',');
            std::getline(fin, tf_in, ';');
            entry::doc d;
            d.id = std::atoi(id_in.c_str());
            d.termFreq = std::atof(tf_in.c_str());
            e.documents.push_back(d);
            if (fin.peek() == '\n' || !fin.good()) {
                fin.get();
                val = false;
            }
        }
        addEntry(e);
    }
    fin.close();
}

void AVLTreeIndex::clear() {
    std::ofstream fout;
    fout.open(filename, std::ios::out | std::ios::trunc);
    if (!fout.is_open()) {
        std::cout << "Error opening " << filename << std::endl;
        exit(1);
    } else {std::cout << filename << " successfully opened." << std::endl;}
    fout.close(); // opened in truncate-option, auto-deletes previous content
    std::cout << filename << " contents cleared." << std::endl;
}

void AVLTreeIndex::find(std::string searchTerm) {
    //AVLTreeNode* node;
    //node = search(keyword);
}

void AVLTreeIndex::addEntry(const entry e) {
    AVLTreeNode* n;
    n->key = e.keyword;
    n->nodeentry = e;
    insert(n);
}

// id -> tfidf
std::map<unsigned int, double> AVLTreeIndex::findAll(std::string keyword) {
    AVLTreeNode* n = search(keyword);
    entry& e = n->nodeentry;
    std::map<unsigned int, double> theMap;
    double idf = calcIDF(treeSize, e.documents.size());
    for(auto it = e.documents.begin(); it != e.documents.end(); it++) theMap[it->id] = calcTFIDF(it->termFreq, idf);
    return theMap;
}
