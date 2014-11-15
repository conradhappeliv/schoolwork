#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <vector>

// abstract interface for index
class Index
{
public:
    Index(std::string filen):filename(filen) {}
    virtual void add(std::string, unsigned int, std::string) = 0;
    virtual void save() = 0;
    virtual void load() = 0;
    virtual void clear() = 0;

    // we can use a hashtable for each of these and actually implement them in this parent class
    std::string IDtoTitle(unsigned int);
    std::string IDtoText(unsigned int);
protected:
    std::string filename;
    struct entry {
        struct doc {
            unsigned int id;
            double termFreq;
        };
        std::string keyword;
        std::vector<doc> documents;
        double idf;
    };
};

#endif // INDEX_H

