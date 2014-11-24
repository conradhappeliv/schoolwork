// Owner: Edward Li

#include "hashtableindex.h"

// constructor
template <typename K, typename V>
HashTableIndex<K,V>::HashTableIndex()
{
    currSize = 0;
    tableSize = TABLE_SIZE;
    threshold = 0.75;
    maxSize = (int)(threshold * tableSize);

    table = new HashEntry*[tableSize];
    for (int i = 0; i < tableSize; i++) table[i] = nullptr;
}

// destructor
template <typename K, typename V>
HashTableIndex<K,V>::~HashTableIndex()
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != nullptr) {
            HashEntry *prev = nullptr;
            HashEntry *entry = table[i];
            while (entry != nullptr) {
                prev = entry;
                entry = entry->getNext();
                delete prev;
            }
        }
    }
    delete[] table;
}

// resize hashtable
template <typename K, typename V>
void HashTableIndex<K,V>::resize()
{
    int oldSize = tableSize;
    tableSize *= 2;
    maxSize = (int) (threshold * tableSize);

    HashEntry **oldTable = table;
    table = new HashEntry*[tableSize];
    for (int i = 0; i < tableSize; i++) table[i] = nullptr;
    currSize = 0;
    for (int j = 0; j < oldSize; j++) {
        if (oldTable[j] != nullptr) {
            HashEntry *oldEntry;
            HashEntry *entry = oldTable[j];
            while (entry != nullptr) {
                insert(entry->getKey(), entry->getValue());
                oldEntry = entry;
                entry = entry->getNext();
                delete oldEntry;
            }
        }
    }
    delete[] oldTable;
}

template <typename K, typename V>
V HashTableIndex<K, V>::get(K key)
{
    int hash = (key % TABLE_SIZE);
    if (table[hash] == nullptr) return -1;
    else {
        HashEntry* entry = table[hash];
        while (entry != nullptr && entry->getKey() != key) entry = entry->getNext();
        if (entry == nullptr) return -1;
        else return entry->getValue();
    }
}

template <typename K, typename V>
void HashTableIndex<K,V>::insert(K key, V value)
{
    int hash = (key % TABLE_SIZE);
    if (table[hash] == nullptr)
    {
        table[hash] = new HashEntry(key, value);
        currSize++;
    } else {
        HashEntry *entry = table[hash];
        while (entry->getNext() != nullptr) entry = entry->getNext();
        if (entry->getKey() == key) entry->setValue(value);
        else {
            entry->setNext(new HashEntry(key, value));
            currSize++;
        }
    }
    if (currSize >= maxSize) resize();
}

template <typename K, typename V>
void HashTableIndex<K,V>::remove(K key)
{
    int hash = (key % TABLE_SIZE);
    if (table[hash] != nullptr) {
        HashEntry *prev = nullptr;
        HashEntry *entry = table[hash];
        while (entry->getNext() != nullptr & entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }
        if (entry->getKey() == key) {
            if (prev == nullptr) {
                HashEntry *nxt = entry->getNext();
                delete entry;
                table[hash] = nxt;
            } else {
                HashEntry *nxt = entry->getNext();
                delete entry;
                prev->setNext(nxt);
            }
            currSize--;
        }
    }
}

template <typename K, typename V>
std::vector<V> HashTableIndex<K, V>::find(K keyword)
{
    // TODO: to be implemented
}
