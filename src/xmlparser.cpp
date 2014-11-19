// Owner: Conrad Appel

#include <iostream>
#include <stack>
#include <mutex>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>

#include "Page.h"
#include "xmlparser.h"
#include "processor.h"

XMLParser::XMLParser(std::string filen) {
    filename = filen;
}

void XMLParser::parse() {
    std::cout << "xml parsing begins" << std::endl;
    xmlpp::TextReader reader(filename);
    while(reader.read()) {
        if(reader.get_name() == "page") { // start of page
            unsigned int id;
            std::string title;
            std::string text;

            // TODO: CLEAN THIS SECTION UP WHEN SURE IT'S WORKING
            // is the data always in order??? we must be careful.
            bool stillReading = true;
            do stillReading = reader.read();
            while(reader.get_name() != "title" && stillReading);
            title = reader.read_string();
            do stillReading = reader.read();
            while(reader.get_name() != "id" && stillReading);
            id = std::atoi(reader.read_string().raw().c_str());
            do stillReading = reader.read();
            while(reader.get_name() != "text" && stillReading);
            text = reader.read_string();

            //if(stillReading) std::cout << id << ": " << title << " - text here" << std::endl;
            TBPLock.lock();
            toBeProcessed.push(Page(id, title, text));
            TBPLock.unlock();
        }
    }
    finished = true;
    std::cout << "xml parsing complete\n";
}

bool XMLParser::complete() {
    return finished;
}

void XMLParser::beginProcessing() {
    Processor::process(toBeProcessed, TBPLock, finished);
}
