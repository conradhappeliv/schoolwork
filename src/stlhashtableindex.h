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
    /// needed for threads
    std::mutex tableLock;
    /// actual index
    std::unordered_map<std::string, entry> table;
    /// used for more efficient loading from file
    void addEntry(const entry);
    bool finishedLoading = true;
};

#endif // STLHashTableIndex_H
