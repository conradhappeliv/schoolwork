#ifndef QUERYPROCESSOR2_H
#define QUERYPROCESSOR2_H

#include "index.h"

#include <vector>

class queryprocessor2
{
public:
    queryprocessor2(Index* index):theIndex(index) {};
    std::vector<unsigned int> processQuery(std::string);
private:
    Index* theIndex;
    bool isQueryOp(const std::string);
};

#endif // QUERYPROCESSOR2_H
