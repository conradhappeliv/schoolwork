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
    //for (int i=0; i < 7465; i++) {
        // format: keyword;idf;id,freq;id,freq;id,freq;

        std::string keyword_in, idf_in, str_in, id_in, tf_in;
        std::getline(fin, keyword_in, ';');
        std::getline(fin, idf_in, ';');
        std::cout << keyword_in << ";" << idf_in << ";";

        bool val = true;
        while(val) {
            std::getline(fin, id_in, ',');
            std::getline(fin, tf_in, ';');
            std::cout << id_in << "," << tf_in << ";";
            if (fin.eof()) {
                //std::cout << "end of line";
                val = false;
            }
        }
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
