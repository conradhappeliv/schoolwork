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
    for (int i = 0; i < tableSize; i++) table[i] = NULL;
}

// destructor
template <typename K, typename V>
HashTableIndex<K,V>::~HashTableIndex()
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL) {
            HashEntry *prev = NULL;
            HashEntry *entry = table[i];
            while (entry != NULL) {
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
    for (int i = 0; i < tableSize; i++) table[i] = NULL;
    currSize = 0;
    for (int j = 0; j < oldSize; j++) {
        if (oldTable[j] != NULL) {
            HashEntry *oldEntry;
            HashEntry *entry = oldTable[j];
            while (entry != NULL) {
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
V HashTableIndex<K,V>::get(K key)
{
    int hash = (key % TABLE_SIZE);
    if (table[hash] == NULL) return -1;
    else {
        HashEntry *entry = table[hash];
        while (entry != NULL && entry->getKey() != key) entry = entry->getNext();
        if (entry == NULL) return -1;
        else return entry->getValue();
    }
}

template <typename K, typename V>
void HashTableIndex<K,V>::insert(K key, V value)
{
    int hash = (key % TABLE_SIZE);
    if (table[hash] == NULL)
    {
        table[hash] = new HashEntry(key, value);
        currSize++;
    } else {
        HashEntry *entry = table[hash];
        while (entry->getNext() != NULL) entry = entry->getNext();
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
    if (table[hash] != NULL) {
        HashEntry *prev = NULL;
        HashEntry *entry = table[hash];
        while (entry->getNext() != NULL & entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }
        if (entry->getKey() == key) {
            if (prev == NULL) {
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
HashEntry* HashTableIndex::find(K keyword)
{
    // TODO: to be implemented
}
