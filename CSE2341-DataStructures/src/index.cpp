// Owner: Conrad Appel

#include <stdexcept>
#include <cmath>

#include "index.h"

double Index::calcTFIDF(double TF, double IDF) {
    return TF * IDF;
}

double Index::calcIDF(unsigned int numInCorpus, unsigned int numWhereTermAppears) {
    return std::log(numInCorpus / std::abs(numWhereTermAppears));
}

void Index::addDoc(const unsigned int id, Page* page) {
    pages.insert(std::pair<unsigned int, Page*>(id, page));
}

const std::string Index::IDtoTitle(const unsigned int id) {
    Page* page = pages[id];
    if(page == nullptr) throw std::invalid_argument("Page doesn't exist");
    return page->title;
}

const std::string Index::IDtoText(const unsigned int id) {
    Page* page = pages[id];
    if(page == nullptr) throw std::invalid_argument("Page doesn't exist");
    return page->body;
}

const Page* Index::IDtoPage(const unsigned int id) {
    Page* page = pages[id];
    if(page == nullptr) throw std::invalid_argument("Page doesn't exist");
    return page;
}
