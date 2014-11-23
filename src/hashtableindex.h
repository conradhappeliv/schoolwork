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
    V get(K key);
    void insert(K key, V value);
    void remove(K key);
    void resize();
    HashEntry<K, V>* find(K keyword); // TODO: to be implemented

private:
    HashEntry<K, V> **table;

    float threshold;
    int tableSize;
    int currSize;
    int maxSize;
};

#endif // HASHTABLEINDEX_H
