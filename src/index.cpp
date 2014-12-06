// Owner: Conrad Appel

#include "index.h"

void Index::addDoc(const unsigned int id, Page* page) {
    pages.insert(std::pair<unsigned int, Page*>(id, page));
}

std::string Index::IDtoTitle(const unsigned int id) {
    Page* page = pages[id];
    if(page == nullptr) return "PageContentsNotLoaded"; // TODO;
    return page->title;
}

std::string Index::IDtoText(const unsigned int id) {
    Page* page = pages[id];
    if(page == nullptr) return "PageContentsNotLoaded"; // TODO;
    return page->body;
}
