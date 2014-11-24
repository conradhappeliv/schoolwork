#include "stlhashtableindex.h"

STLHashTableIndex::STLHashTableIndex(std::string filename):Index(filename) {
    table.reserve(1000000);
}

void STLHashTableIndex::add(const unsigned int id, const std::string word, const unsigned int freq) {
    entry::doc d;
    d.id = id;
    d.termFreq = freq;
    tableLock.lock();
    entry& e = table[word];
    if(e.keyword != word) e.keyword = word;
    e.documents.push_back(d);
    tableLock.unlock();
}

void STLHashTableIndex::save() {

}

void STLHashTableIndex::load() {

}

void STLHashTableIndex::clear() {

}
