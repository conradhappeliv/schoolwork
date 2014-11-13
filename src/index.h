#ifndef INDEX_H
#define INDEX_H

#include <string>

// abstraction layer on top of either AVL tree or hash table
class Index
{
public:
    virtual void addEntry(std::string) = 0;
    virtual void saveToFile(std::string) = 0;
    
};

#endif // INDEX_H
