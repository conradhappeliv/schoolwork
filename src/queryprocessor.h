// Owner: Edward Li

#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H
#include "hashentry.h"
#include "hashtableindex.h"
#include "avltreeindex.h"
#include <vector>

template <typename K, typename V>
class queryprocessor
{
public:
    queryprocessor(int indextype);
    void processQuery();
    void search(std::string term, std::string delim);
    //void printResults();

private:
    int mode;
    //std::vector<std::string> AVLSearchResults;
    //std::vector<K> hashSearchResults;
};

#endif // QUERYPROCESSOR_H
