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
    XMLParser(std::vector<std::string>, Index*);
    /// add all documents to a stack to be used elsewhere
    void parse();
    /// returns whether still parsing
    bool complete();
    /// starts a processor
    void beginProcessing();
    /// combines parsing and processing into one multi-threaded super function
    void threadedParseAndProcess();
    /// parses and adds all documents to index, but skips processing (for lookup tables)
    void addDocsNoProcessing();
private:
    /// files to parse
    std::vector<std::string> filenames;
    /// index to add to
    Index* index;
    int count = 0;
    bool finished = false;
    /// prevents data races in stack
    std::mutex TBPLock;
    /// parser puts all documents here to be processed by the processor
    std::stack<Page*> toBeProcessed;
};

#endif // XMLPARSER_H
