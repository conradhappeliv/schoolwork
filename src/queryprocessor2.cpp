#include "queryprocessor2.h"
#include "processor.h"

#include <sstream>
#include <unordered_map>
#include <set>

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
    std::unordered_map<std::string, std::multimap<unsigned int, double>> words;
        // ANDs
        for(auto it = ANDs.begin(); it != ANDs.end(); it++) {
            if(it == ANDs.begin()) {
                auto res = theIndex->findAll(*it);
                for(auto it2 = res.begin(); it2 != res.end(); it2++) {
                    words[*it].emplace(it2->first, it2->second);
                }
            } else {
                auto res = theIndex->findAll(*it);
                for(auto it2 = res.begin(); it2 != res.end(); it2++) {
                    if(words[*it].find(it2->first) == words[*it].end()) words.erase(*it); // word doesn't exist before
                }
                if(words.empty()) break; // not all words->pages intersect
            }
        }
        // ORs
        for(auto it = ORs.begin(); it != ORs.end(); it++) {
            auto res = theIndex->findAll(*it);
            for(auto it2 = res.begin(); it2 != res.end(); it2++) {
                words[*it].emplace(it2->first, it2->second);
            }
        }
        // NOTs
        for(auto it = NOTs.begin(); it != NOTs.end(); it++) {
            auto res = theIndex->findAll(*it);
            for(auto it2 = res.begin(); it2 != res.end(); it2++) {
                for(auto it3 = words.begin(); it3 != words.end(); it3++) {
                    if(it3->second.find(it2->first) != it3->second.end()) {
                        words.erase(it3);
                        break;
                    }
                }
            }
        }

    // order results by tf-idf
    std::multimap<double, unsigned int> sorted; // this map should automatically sort by key (if-idf)
    for(auto it = words.begin(); it != words.end(); it++) {
        for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            sorted.insert(std::pair<double, unsigned int>(it2->second, it2->first));
        }
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
