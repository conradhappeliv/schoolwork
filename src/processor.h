#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stack>
#include <unordered_map>
#include <forward_list>
#include <mutex>

#include "Page.h"

class Processor {
public:
    Processor();
    void process(std::stack<Page>&, std::mutex&, bool&); // TODO: this bool reference is probably bad practice lol
private:
    static bool isStopWord(std::string);
    std::unordered_map<std::string, unsigned int> frequencies;
    std::forward_list<std::string> words;
};

#endif // PROCESSOR_H
