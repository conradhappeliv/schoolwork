// Owner: Edward Li

#ifndef HASHTABLEINDEX_H
#define HASHTABLEINDEX_H
#include "hashentry.h"

const int TABLE_SIZE = 1000;

template <typename K, typename V>
class HashTableIndex
{
public:
    HashTableIndex();
    ~HashTableIndex();
    int get(K key);
    void insert(K key, V value);
    void remove(K key);
    void resize();
    HashEntry* find(K keyword); // TODO: to be implemented

private:
    HashEntry **table;

    float threshold;
    int tableSize;
    int currSize;
    int maxSize;
};

#endif // HASHTABLEINDEX_H
