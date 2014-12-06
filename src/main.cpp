// Owner: Conrad Appel

#include <iostream>
#include <thread>

#include "lib/getopt_pp.h"
#include "src/xmlparser.h"
#include "src/index.h"
#include "src/queryprocessor2.h"
#include "src/stlhashtableindex.h"
#include "src/stresstest.h"

enum modes {
    MAINTENANCE,
    INTERACTIVE,
    STRESS,
    HELP
};
enum indextypes {
    AVLTREE,
    HASHTABLE
};

std::string indexpath = "./default.index";

int main(int argc, char* argv[])
{
    int mode = HELP; // default mode

    // mode option parsing
    GetOpt::GetOpt_pp ops(argc, argv);

    if(ops >> GetOpt::OptionPresent('h', "help")) mode = HELP;
    else if(ops >> GetOpt::OptionPresent('i', "interactive")) mode = INTERACTIVE;
    else if(ops >> GetOpt::OptionPresent('s', "stresstest")) mode = STRESS;
    else if(ops >> GetOpt::OptionPresent('m', "maintenance")) mode = MAINTENANCE;
    else mode = HELP;

    // optparsing and execution specific to modes
    if(mode == MAINTENANCE) {
        std::cout << "~~~ MAINTENANCE MODE ~~~" << std::endl;
        std::string filepath;
        if(ops >> GetOpt::Option('f', "filename", filepath)) { // add file to index
            Index* index = new STLHashTableIndex(indexpath);
            if(ops >> GetOpt::OptionPresent('a', "append")) {
                index->load();
            }
            XMLParser parser(filepath, index);
            parser.threadedParseAndProcess();
            index->save();
        } else if(ops >> GetOpt::OptionPresent('c', "clear")){ // clear index
            Index* index = new STLHashTableIndex(indexpath);
            index->clear();
        } else if(ops >> GetOpt::OptionPresent('o', "open")) { // open index file TEST FUNCTIONALITY
            Index* index = new STLHashTableIndex(indexpath);
            index->load();
        } else { // show help relevant to maintenance mode
            std::cout << "Invalid usage. \"./searchengine --help\" for usage instructions." << std::endl;
        }
    } else if(mode == INTERACTIVE) {
        std::cout << "~~~ INTERACTIVE MODE ~~~" << std::endl;

        std::string filepath;
        Index* index;
        int indexType = HASHTABLE; // default index type

        if(ops >> GetOpt::Option('a', "avltree", filepath)) {
            indexType = AVLTREE;
            // declare new AVLTreeIndex
        } else if(ops >> GetOpt::Option('t', "hashtable", filepath)) {
            indexType = HASHTABLE;
        }

        // user-defined index file if they want
        ops >> GetOpt::Option('p', "indexpath", indexpath);

        if(indexType == HASHTABLE) index = new STLHashTableIndex(indexpath);
        // else if(indexType == AVLTREE) index = TODO:
        std::cout << "Loading " << indexpath << std::endl;
        index->load();
        std::cout << "Index loaded." << std::endl;

        queryprocessor2 query_me(index);

        // enter a loop to allow the user to search index and process queries
        while (true) {
            char q[100000];

            std::cout << "Please enter a search query, \"retrieve [page_id]\", or \"quit\": ";
            std::cin.getline(q, 100000);
            std::string query(q);
            if (query == "exit") break;
            else if(query.compare(0, 8, "retrieve") == 0) {
                std::string display_me = query.substr(9, std::string::npos);
                unsigned int page_id = std::atoi(display_me.c_str());
                display_me += ": ";
                display_me += index->IDtoTitle(page_id) + '\n';
                display_me += index->IDtoText(page_id);
                std::cout << display_me << std::endl;
            } else {
                auto results = query_me.processQuery(query);
                for(auto it = results.begin(); it != results.end(); it++) {
                    std::cout << *it << ": " << index->IDtoTitle(*it) << std::endl;
                }
            }
        }
    } else if(mode == STRESS) {
        std::cout << "~~~ STRESS TEST MODE ~~~" << std::endl;
        std::string filepath;
        if(ops >> GetOpt::GlobalOption(filepath)) { // run commands
            StressTest test_it(filepath);
        } else { // show stress-test mode help
            std::cout << "Must specify a filename of a test." << std::endl;
        }
    } else if(mode == HELP) {
        system("man -l ../searchengine.1");
    }

    return 0;
}

