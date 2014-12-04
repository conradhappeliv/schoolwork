// Owner: Conrad Appel

#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <stack>
#include <mutex>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>

#include "Page.h"
#include "processor.h"

class XMLParser {
public:
    XMLParser(std::string, Index*);
    void parse();
    bool complete();
    void beginProcessing();
    void threadedParseAndProcess();
private:
    std::string filename;
    Index* index;
    int count = 0;
    bool finished = false;
    std::mutex TBPLock;
    std::stack<Page*> toBeProcessed;
};

#endif // XMLPARSER_H
