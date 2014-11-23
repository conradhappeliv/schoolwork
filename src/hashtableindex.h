#ifndef HASHTABLEINDEX_H
#define HASHTABLEINDEX_H
#include "HashEntry.h"

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
    V find(K key);

private:
    HashEntry **table;

    float threshold;
    int tableSize;
    int currSize;
    int maxSize;
};

#endif // HASHTABLEINDEX_H
