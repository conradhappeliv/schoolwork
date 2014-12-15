#ifndef QUERYPROCESSOR2_H
#define QUERYPROCESSOR2_H

#include "index.h"

#include <vector>

class queryprocessor2
{
public:
    /// constructor take a reference to an index from which it should query
    queryprocessor2(Index* index):theIndex(index) {}
    /// given line query, returns a vector of page ids matching query
    std::vector<unsigned int> processQuery(std::string);
private:
    /// reference to index to run queries on
    Index* theIndex;
    /// returns true for AND, OR, NOT
    bool isQueryOp(const std::string);
};

#endif // QUERYPROCESSOR2_H
