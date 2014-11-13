#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>

class XMLParser
{
public:
    XMLParser(std::string);
    void parse();
    bool complete();
private:
    std::string filename;
    int count = 0;
    bool finished = false;
};

#endif // XMLPARSER_H
