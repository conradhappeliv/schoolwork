// Owner: Edward Li

#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <vector>
#include <string>

class queryprocessor
{
public:
    queryprocessor(int indextype);
    std::vector<std::string> processQuery(std::string query);
    //void search(std::string term, std::string delim);
    //void printResults();

private:
    int mode;
    //std::vector<std::string> AVLSearchResults;
    //std::vector<K> hashSearchResults;
};

#endif // QUERYPROCESSOR_H
