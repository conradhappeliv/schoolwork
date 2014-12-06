// Owner: Conrad Appel

#include <stdexcept>

#include "index.h"

void Index::addDoc(const unsigned int id, Page* page) {
    pages.insert(std::pair<unsigned int, Page*>(id, page));
}

std::string Index::IDtoTitle(const unsigned int id) {
    Page* page = pages[id];
    if(page == nullptr) throw std::invalid_argument("Page doesn't exist");
    return page->title;
}

std::string Index::IDtoText(const unsigned int id) {
    Page* page = pages[id];
    if(page == nullptr) throw std::invalid_argument("Page doesn't exist");
    return page->body;
}
