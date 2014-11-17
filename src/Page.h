#ifndef PAGE_H
#define PAGE_H

struct Page {
    Page(unsigned int i, std::string titl, std::string bod):id(i),title(titl),body(bod) {}
    unsigned int id;
    std::string title;
    std::string body;
};

#endif // PAGE_H
