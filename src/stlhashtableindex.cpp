// Owner: Edward Li

#include "stlhashtableindex.h"
#include <iostream>
#include <fstream>

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
    std::ofstream fout;
    fout.open(filename);
    if (!fout.is_open()) {
        std::cout << "Error opening " << filename << std::endl;
        exit(1);
    } else {std::cout << filename << " successfully opened." << std::endl;}

    // write out all data to file
    for (auto i = table.begin(); i != table.end(); i++) {
        // format: keyword;idf;id,freq;id,freq;id,freq;
        fout << i->first << ";";
        fout << i->second.idf << ";";
        for (auto j = i->second.documents.begin(); j != i->second.documents.end(); j++) {
            fout << j->id << ",";
            fout << j->termFreq << ";";
        }
        fout << "\n";
    }
    fout << "?";
    fout.close();
}

void STLHashTableIndex::load() {
    std::ifstream fin;
    fin.open(filename);
    if (!fin.is_open()) {
        std::cout << "Error opening " << filename << std::endl;
        exit(1);
    } else {std::cout << filename << " successfully opened." << std::endl;}

    // read in index from file
    while (!fin.eof()) {
        entry e;
        std::string keyword_in, idf_in, str_in, id_in, tf_in;
        std::getline(fin, keyword_in, ';');
        std::getline(fin, idf_in, ';');
        e.keyword = keyword_in;
        e.idf = std::atoi(idf_in.c_str());
        //std::cout << keyword_in << ";" << idf_in << ";";

        bool val = true;
        while(val) {
            std::getline(fin, id_in, ',');
            std::getline(fin, tf_in, ';');
            entry::doc d;
            d.id = std::atoi(id_in.c_str());
            d.termFreq = std::atoi(tf_in.c_str());
            e.documents.push_back(d);
            //std::cout << id_in << "," << tf_in << ";";
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
}

void STLHashTableIndex::clear() {

}

void STLHashTableIndex::find(std::string searchTerm) {
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
    else std::cout << "search term not found\n";
}

std::map<unsigned int, unsigned int> STLHashTableIndex::findAll(std::string keyword) {
    try {
        entry& e = table.at(keyword);
        std::map<unsigned int, unsigned int> theMap;
        for(auto it = e.documents.begin(); it != e.documents.end(); it++) theMap[it->id] = it->termFreq;
        return theMap;
    } catch(std::out_of_range) {
        std::cout << "Keyword doesn't exist" << std::endl;
        std::map<unsigned int, unsigned int> theMap;
        return theMap;
    }
}

void STLHashTableIndex::addEntry(const entry e) {
    table[e.keyword] = e;
}
