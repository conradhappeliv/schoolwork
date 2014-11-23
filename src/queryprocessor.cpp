// Owner: Edward Li

#include "queryprocessor.h"
#include <iostream>
#include <sstream>
using namespace std;

enum indextype {
    AVLTREE,
    HASHTABLE
};

queryprocessor::queryprocessor(int indextype)
{
    if (indextype == AVLTREE) mode = AVLTREE;
    else mode = HASHTABLE;
}


void queryprocessor::processQuery()
{
    char q[100];

    cout << "Please enter a search query: ";
    cin.getline(q, 100);
    string query(q);
    istringstream ss(query);

    string first;
    ss >> first;
    while (!ss.eof()) {
        string term;
        ss >> term;
        cout << "TERM: " << term << endl;
        if (first == "AND") {
            // find intersection of terms searched
            cout << "intersection" << endl;
            search(term, "AND");
        } else if (first == "OR") {
            // find union of terms searched
            cout << "union" << endl;
            search(term, "OR");
        } else {
            // single term or no delimiters
            cout << "continue" << endl;
            search(first, NULL);
            search(term, NULL);
        }

        if (term == "NOT") {
            ss.ignore(25, ' ');
            while (!ss.eof()) {
                string remove;
                ss >> remove;
                cout << "NOT " << remove << endl;
                search(remove, "NOT");
            }
        }
    }
}

template <typename K, typename V>
void queryprocessor<K,V>::search(string term, string delim)
{
    if (mode == AVLTREE) { // working with AVL Tree nodes
        // look for avl node with matching term and keyword
        /*
        if (resulting node doesnt exist {
            cout << "search term not found" << endl;
            break;
        }

        if (delim == "OR") {
            add to vector all documents with search term;
        } else if (delim == "AND") {
            add all documents with each search term, and find intersection using set_intersection
        } else if (delim == "NOT") {
            search vector for this term
            delete nodes with term
        } else {
            AVLSearchResults.push_back(resulting node);
        */
    }
    else { // working with Hash Table entries
        // repeat pseudocode in AVL tree mode
    }

    //printResults(vector);
}

/*
template <typename K, typename V>
void queryprocessor::printResults()
{

}
*/
