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
    /// file from which index is saved and loaded
    std::string filename;
    struct entry {
        struct doc {
            unsigned int id;
            /// calculated with augmented term frequency equation
            double termFreq;
        };
        std::string keyword;
        /// documents that contain this keyword
        std::vector<doc> documents;
    };
    /// files that were added to this index
    std::vector<std::string> references;

    static double calcTFIDF(double TF, double IDF);
    static double calcIDF(unsigned int numInCorpus, unsigned int numWhereTermAppears);
public:
    Index(std::string filen):filename(filen) {
        pages.reserve(256279);
    }
    /// adds a file that this index loaded from
    void addReference(std::string filen) { references.push_back(filen); }
    virtual ~Index() {}
    /// adds a new entry or a new document reference to the index
    virtual void add(const unsigned int, const std::string, const double) = 0;
    /// adds a document's contents to a lookup table in memory
    void addDoc(const unsigned int id, Page* page);
    /// saves index to "filename"
    virtual void save() = 0;
    /// loads index from "filename"
    virtual void load() = 0;
    /// empties the index in memory
    virtual void clear() = 0;
    /// returns all docId->tfidfs with specified keyword
    virtual std::map<unsigned int, double> findAll(std::string) = 0;
    /// returns whether or not the index is finished loading in memory (needed for multithreads)
    virtual bool loaded() { return true; }

    /// gets from lookup table "pages"
    const std::string IDtoTitle(const unsigned int id);
    /// gets from lookup table "pages"
    const std::string IDtoText(const unsigned int id);
    /// gets from lookup table "pages"
    const Page* IDtoPage(const unsigned int id);
private:
    struct pageContents {
        pageContents() {}
        pageContents(std::string t, std::string b):title(t),body(b) {}
        std::string title;
        std::string body;
    };
    /// lookup table for document information
    std::unordered_map<unsigned int, Page*> pages;
};

#endif // INDEX_H

