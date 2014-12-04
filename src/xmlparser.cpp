// Owner: Conrad Appel

#include <iostream>
#include <stack>
#include <mutex>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include <thread>

#include "Page.h"
#include "xmlparser.h"
#include "processor.h"

XMLParser::XMLParser(std::string filen, Index* inde) {
    filename = filen;
    index = inde;
}

void XMLParser::parse() {
    std::cout << "xml parsing begins" << std::endl;
    xmlpp::TextReader reader(filename);
    while(reader.read()) {
        if(reader.get_name() == "page") { // start of page
            unsigned int id;
            std::string title;
            std::string text;
            std::string timestamp;
            std::string username;

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
            while(reader.get_name() != "timestamp" && stillReading);
            timestamp = reader.read_string();
            do stillReading = reader.read();
            while(reader.get_name() != "username" && stillReading);
            username = reader.read_string();
            do stillReading = reader.read();
            while(reader.get_name() != "text" && stillReading);
            text = reader.read_string();

            Page* p = new Page;
            p->body = text;
            p->date = timestamp;
            p->id = id;
            p->title = title;
            p->username = username;
            TBPLock.lock();
            toBeProcessed.push(p);
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
    while(finished);
    Processor::process(toBeProcessed, TBPLock, &finished, index);
}

void XMLParser::threadedParseAndProcess() {
    std::thread threads[2];
    threads[0] = std::thread([&]() {
        parse();
    });
    threads[1] = std::thread([&]() {
        beginProcessing();
    });
    threads[0].join();
    threads[1].join();
}
