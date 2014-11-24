// Owner: Edward Li

#ifndef HASHTABLEINDEX_H
#define HASHTABLEINDEX_H

const int TABLE_SIZE = 1000;

template <typename K, typename V>
class HashTableIndex
{

private:
    struct HashEntry {
        HashEntry(const K &key, const V &val):keyword(key), value(val), next(NULL) {}
        K getKey() const {return keyword;}
        V getValue() const {return value;}
        void setValue(V value) {
           this->value = value;
        }
        HashEntry* getNext() {return next;}
        void setNext(HashEntry *next) {
            this->next = next;
        }

        K keyword;
        V value;
        HashEntry *next;
    };

public:
    HashTableIndex();
    ~HashTableIndex();
    V get(K key);
    void insert(K key, V value);
    void remove(K key);
    void resize();
    //HashEntry* find(K keyword); // TODO: to be implemented
    HashEntry<K, V>* find(K keyword); // TODO: to be implemented

private:
    HashEntry<K, V> **table;

    float threshold;
    int tableSize;
    int currSize;
    int maxSize;
};

#endif // HASHTABLEINDEX_H
