// Owner: Conrad Appel

#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <map>

#include "Page.h"

// abstract interface for index
class Index {
protected:
    std::string filename;
    struct entry {
        struct doc {
            unsigned int id;
            double termFreq;
        };
        std::string keyword;
        std::vector<doc> documents;
    };
    std::string indexReferenced;

    static double calcTFIDF(double, double);
    static double calcIDF(unsigned int, unsigned int);
public:
    Index(std::string filen):filename(filen) {
        pages.reserve(256279);
    }
    virtual ~Index() {}
    void setIndexFile(std::string filen) { indexReferenced = filen; }
    virtual void add(const unsigned int, const std::string, const double) = 0;
    void addDoc(const unsigned int, Page*);
    virtual void save() = 0;
    virtual void load() = 0;
    virtual void clear() = 0;
    virtual void find(std::string) = 0;
    virtual std::map<unsigned int, double> findAll(std::string) = 0;

    const std::string IDtoTitle(const unsigned int);
    const std::string IDtoText(const unsigned int);
    const Page* IDtoPage(const unsigned int);
private:
    struct pageContents {
        pageContents() {}
        pageContents(std::string t, std::string b):title(t),body(b) {}
        std::string title;
        std::string body;
    };
    std::unordered_map<unsigned int, Page*> pages;
};

#endif // INDEX_H

