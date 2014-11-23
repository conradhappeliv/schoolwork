#ifndef HASHENTRY_H
#define HASHENTRY_H
#include <string>
//#include <iostream>

template <typename K, typename V>
class HashEntry
{
public:
    HashEntry(K key, V value);
    K getKey();
    V getValue();
    void setValue(V value);
    HashEntry* getNext();
    void setNext(HashEntry *next);

private:
    K keyword;
    V value;
    HashEntry *next;
};

#endif // HASHENTRY_H
