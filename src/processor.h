// Owner: Conrad Appel

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
    static void process(std::stack<Page>&, std::mutex&, bool&); // TODO: this bool reference is probably bad practice lol
    static bool isStopWord(std::string);
private:
};

#endif // PROCESSOR_H
