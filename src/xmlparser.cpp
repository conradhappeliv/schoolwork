#include <iostream>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>

#include "xmlparser.h"

XMLParser::XMLParser(std::string filen) {
    filename = filen;
}

void XMLParser::parse() {
    xmlpp::TextReader reader(filename);
    while(reader.read()) {
        if(reader.get_name() == "page") { // start of page
            std::string id;
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
            id = reader.read_string();
            do stillReading = reader.read();
            while(reader.get_name() != "text" && stillReading);
            text = reader.read_string();

            //if(stillReading) std::cout << id << ": " << title << " - text here" << std::endl;
        }
    }
    finished = true;
    std::cout << "xml parsing complete" << std::endl;
}

bool XMLParser::complete() {
    return finished;
}
