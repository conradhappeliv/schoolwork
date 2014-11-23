// Owner: Edward Li

#include "hashentry.h"

template <typename K, typename V>
HashEntry<K,V>::HashEntry(K key, V value)
{
    key = keyword;
    this->value = value;
    this->next = NULL;
}

template <typename K, typename V>
K HashEntry<K,V>::getKey()
{
    return keyword;
}

// TODO: correct this to support entries
template <typename K, typename V>
V HashEntry<K,V>::getValue()
{
    return value;
}

template <typename K, typename V>
void HashEntry<K,V>::setValue(V value)
{
    this->value = value;
}

template <typename K, typename V>
HashEntry* HashEntry<K,V>::getNext()
{
    return next;
}

template <typename K, typename V>
void HashEntry<K,V>::setNext(HashEntry *next)
{
    this->next = next;
}
