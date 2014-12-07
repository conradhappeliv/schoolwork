// Owner: Edward Li

#ifndef STLHashTableIndex_H
#define STLHashTableIndex_H

#include <unordered_map>
#include <map>
#include <mutex>

#include "index.h"

class STLHashTableIndex : public Index
{
public:
    STLHashTableIndex(std::string);
    virtual void add(const unsigned int, const std::string, const double);
    virtual void save();
    virtual void load();
    virtual void clear();
    virtual std::map<unsigned int, double> findAll(std::string);
    bool loaded();
private:
    std::mutex tableLock;
    std::unordered_map<std::string, entry> table;
    void addEntry(const entry);
    bool finishedLoading = true;
};

#endif // STLHashTableIndex_H
