// Owner: Edward Li

#include "stlhashtableindex.h"
#include "xmlparser.h"

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>

STLHashTableIndex::STLHashTableIndex(std::string filename):Index(filename) {
    table.reserve(1000000);
}

void STLHashTableIndex::add(const unsigned int id, const std::string word, const double freq) {
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
    std::ofstream fout;
    fout.open(filename);
    if (!fout.is_open()) {
        std::cout << "Error opening " << filename << std::endl;
        throw std::invalid_argument("file was unable to be opened");
    }

    for(auto it = references.begin(); it != references.end(); it++) {
        if((*it)[0] != '/') {
            (*it).insert(0, "/");
            char c[PATH_MAX];
            getcwd(c, PATH_MAX);
            (*it).insert(0, c);
        }
        fout << *it << std::endl;
    }

    // write out all data to file
    fout << "ENDREFS" << std::endl;
    for (auto i = table.begin(); i != table.end(); i++) {
        fout << i->first << ";";
        for (auto j = i->second.documents.begin(); j != i->second.documents.end(); j++) {
            fout << j->id << ",";
            fout << j->termFreq << ";";
        }
        fout << "\n";
    }
    fout.close();
}

void STLHashTableIndex::load() {
    std::ifstream fin;
    fin.open(filename);
    if (!fin.is_open()) {
        std::cout << "Error opening " << filename << std::endl;
        return;
    }

    // read in index from file
    std::string ref;
    do {
        std::getline(fin, ref);
        if(ref != "ENDREFS") this->addReference(ref);
    } while(ref != "ENDREFS");
    std::thread parse = std::thread([&]() {
        XMLParser parser(references, this);
        parser.parse();
        parser.addDocsNoProcessing();
    });

    while (!fin.eof()) {
        entry e;
        std::string keyword_in, id_in, tf_in;
        std::getline(fin, keyword_in, ';');
        e.keyword = keyword_in;

        bool val = true;
        while(val) {
            std::getline(fin, id_in, ',');
            std::getline(fin, tf_in, ';');
            entry::doc d;
            d.id = std::atoi(id_in.c_str());
            d.termFreq = std::atof(tf_in.c_str());
            e.documents.push_back(d);
            if (fin.peek() == '\n' || !fin.good()) {
                fin.get();
                //std::cout << "end of line";
                val = false;
            }
        }
        addEntry(e);
        //std::cout << std::endl;
    }
    fin.close();
    parse.join();
}

void STLHashTableIndex::clear() {
    table.clear();
}
void STLHashTableIndex::find(std::string searchTerm) {
    /*
    auto srch = table.find(searchTerm);
    if (srch != table.end()) {
        std::cout << "SEARCH TERM: " << srch->first << std::endl;
        std::cout << "*****RESULTS*****" << std::endl;
        for (auto j = srch->second.documents.begin(); j != srch->second.documents.end(); j++) {
            std::cout << "doc ID: " << j->id << std::endl;
            const unsigned int temp_id = j->id;
            std::string idfromtitle = IDtoTitle(temp_id);
            std::cout << "title: " << idfromtitle << "\n\n";
        }

    }
    else std::cout << "search term not found\n";*/
}

// id -> tfidf
std::map<unsigned int, double> STLHashTableIndex::findAll(std::string keyword) {
    entry& e = table[keyword];
    std::map<unsigned int, double> theMap;
    double idf = calcIDF(table.size(), e.documents.size());
    for(auto it = e.documents.begin(); it != e.documents.end(); it++) theMap[it->id] = calcTFIDF(it->termFreq, idf);
    return theMap;
}

void STLHashTableIndex::addEntry(const entry e) {
    table[e.keyword] = e;
}
