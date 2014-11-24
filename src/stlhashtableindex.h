#ifndef STLHashTableIndex_H
#define STLHashTableIndex_H

#include <unordered_map>
#include <mutex>

#include "index.h"

class STLHashTableIndex : public Index
{
public:
    STLHashTableIndex(std::string);
    virtual void add(const unsigned int, const std::string, const unsigned int);
    virtual void save();
    virtual void load();
    virtual void clear();
private:
    std::mutex tableLock;
    std::unordered_map<std::string, entry> table;
};

#endif // STLHashTableIndex_H
