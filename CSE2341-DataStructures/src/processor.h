// Owner: Conrad Appel

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stack>
#include <unordered_map>
#include <forward_list>
#include <mutex>

#include "Page.h"
#include "index.h"

class Processor {
public:
    Processor();
    /// processes all words parsed by the parser and adds them to index
    static void process(std::stack<Page*>& toBeProcessed, std::mutex& TBPLock, const bool* completedParsing, Index* index);
    static bool isStopWord(std::string word);
    static void stemWord(std::string& word); // for use by the outside world
    /// removes punctuation, removes stop words, stems
    static void prepareWord(std::string& word);
    /// removes punctuation, removes stop words, stems with given stemmer (more efficient when can be shared)
    static void prepareWord(std::string& word, struct stemmer* theStemmer);
private:
};

#endif // PROCESSOR_H
