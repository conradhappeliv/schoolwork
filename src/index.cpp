// Owner: Conrad Appel

#include "index.h"

void Index::addDoc(const unsigned int id, Page* page) {
    pages.insert(std::pair<unsigned int, Page*>(id, page));
}

std::string Index::IDtoTitle(const unsigned int id) {
    return pages[id]->title;
}

std::string Index::IDtoText(const unsigned int id) {
    return pages[id]->body;
}
