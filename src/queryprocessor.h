// Owner: Edward Li

#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <vector>
#include <string>

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
