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
    static void process(std::stack<Page*>&, std::mutex&, const bool*, Index*); // TODO: this bool reference is probably bad practice lol
    static bool isStopWord(std::string);
    static void stemWord(std::string&); // for use by the outside world
private:
};

#endif // PROCESSOR_H
