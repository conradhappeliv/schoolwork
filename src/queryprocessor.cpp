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


std::vector<std::string> queryprocessor::processQuery(std::string query)
{
    std::istringstream ss(query);
    std::vector<std::string> processedQueries;

    string first;
    ss >> first;

    if (first == "AND") {
        // find intersection of terms searched
        cout << "intersection" << endl;
        while (!ss.eof()) {
            string term;
            ss >> term;
            cout << "TERM: " << term << endl;
            //processedQueries.push_back(term, "AND");
            if (term == "NOT") {
                ss.ignore(25, ' ');
                while (!ss.eof()) {
                    string remove;
                    ss >> remove;
                    cout << "NOT " << remove << endl;
                    //search(remove, "NOT");
                }
            }

        }
    } else if (first == "OR") {
        // find union of terms searched
        cout << "union" << endl;
        while (!ss.eof()) {
            string term;
            ss >> term;
            cout << "TERM: " << term << endl;
            //processedQueries.push_back(term, "OR");
            if (term == "NOT") {
                ss.ignore(25, ' ');
                while (!ss.eof()) {
                    string remove;
                    ss >> remove;
                    cout << "NOT " << remove << endl;
                    //search(remove, "NOT");
                }
            }

        }
    } else {
        // single term or no delimiters
        cout << "no delim" << endl;
        cout << first << endl;
        processedQueries.push_back(first);
        while (!ss.eof()) {
            string term;
            ss >> term;
            cout << term << endl;
            processedQueries.push_back(term);
            if (term == "NOT") {
                ss.ignore(25, ' ');
                while (!ss.eof()) {
                    string remove;
                    ss >> remove;
                    cout << "NOT " << remove << endl;
                    //search(remove, "NOT");
                }
            }

        }
    }

    /*if (term == "NOT") {
        ss.ignore(25, ' ');
        while (!ss.eof()) {
            string remove;
            ss >> remove;
            cout << "NOT " << remove << endl;
            //search(remove, "NOT");
        }
    }*/
    return processedQueries;
}

/*
void queryprocessor::search(string term, string delim) {
    if (mode == AVLTREE) { // working with AVL Tree nodes
        // look for avl node
 with matching term and keyword

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

    } else { // working with Hash Table entries
        // look for hash table entry with matching term and keyword
        // add in differentiation for delims later
        //if (false) {
        //    cout << "search term not found" << endl;
        //    break;
        //}
    }

    //printResults(vector);
}

template <typename K, typename V>
void queryprocessor::printResults()
{

}
*/
