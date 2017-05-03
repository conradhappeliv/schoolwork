#include "queryprocessor2.h"
#include "processor.h"

#include <sstream>
#include <unordered_map>
#include <set>
#include <iostream>


std::vector<unsigned int> queryprocessor2::processQuery(std::string queryLine) {
    std::set<std::string> ANDs;
    std::set<std::string> ORs;
    std::set<std::string> NOTs;

    // parse the line
    std::stringstream stream(queryLine);
    std::string curWord, curOp;
    stream >> curWord;
    if(!isQueryOp(curWord)) { // no initial boolean query
        curOp = "AND";
        Processor::prepareWord(curWord);
        ANDs.insert(curWord);
    } else curOp = curWord;

    while(stream.good()) {
        stream >> curWord;
        if(isQueryOp(curWord)) curOp = curWord;
        else {
            Processor::prepareWord(curWord);
            if(curWord == "") continue;
            if(curOp == "AND") ANDs.insert(curWord);
            else if(curOp == "OR") ORs.insert(curWord);
            else if(curOp == "NOT") NOTs.insert(curWord);
        }
    }

    // gather all the stuff & set operations along the way
    // this map is term -> multimap(page_id -> tf-idf)
    std::map<unsigned int, double> words;
        // ANDs
        for(auto it = ANDs.begin(); it != ANDs.end(); it++) {
            auto res = theIndex->findAll(*it);
            if(it == ANDs.begin()) {
                words.swap(res);
            } else {
                for(auto it2 = words.begin(); it2 != words.end(); it2++) {
                    auto res_word = res.find(it2->first);
                    if(res_word == res.end()) words.erase(it2);
                    else it2->second += res_word->second; // increase ranking
                }
            }
            if(words.empty()) break;
        }

        // ORs
        // TODO: should words with multiple OR terms have a higher ranking?? That's how it is currently
        for(auto it = ORs.begin(); it != ORs.end(); it++) {
            auto res = theIndex->findAll(*it);
            for(auto it2 = res.begin(); it2 != res.end(); it2++) words[it2->first] += it2->second;
        }

        // NOTs
        for(auto it = NOTs.begin(); it != NOTs.end(); it++) {
            auto res = theIndex->findAll(*it);
            for(auto it2 = res.begin(); it2 != res.end(); it2++) words.erase(it2->first);
        }

    // order results by tf-idf
    std::multimap<double, unsigned int> sorted; // this map should automatically sort by key (if-idf)
    for(auto it = words.begin(); it != words.end(); it++) {
        sorted.insert(std::pair<double, unsigned int>(it->second, it->first));
    }

    // then transfer results to return vector of page ids
    std::vector<unsigned int> return_me;
    for(auto it = sorted.cbegin(); it != sorted.cend(); it++) return_me.push_back(it->second);

    return return_me;
}

bool queryprocessor2::isQueryOp(const std::string word) {
    if(word == "AND" || word == "OR" || word == "NOT") return true;
    return false;
}
