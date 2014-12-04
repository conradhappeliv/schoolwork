// Owner: Conrad Appel

#include <iostream>
#include <thread>

#include "lib/getopt_pp.h"
#include "src/xmlparser.h"
#include "src/index.h"
#include "src/queryprocessor.h"
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

const std::string indexpath = "./default.index";



int main(int argc, char* argv[])
{
    int mode = HELP; // default mode

    // mode option parsing
    GetOpt::GetOpt_pp ops(argc, argv);
    if(ops >> GetOpt::OptionPresent('m', "maintenance")) mode = MAINTENANCE;
    else if(ops >> GetOpt::OptionPresent('i', "interactive")) mode = INTERACTIVE;
    else if(ops >> GetOpt::OptionPresent('s', "stresstest")) mode = STRESS;
    else if(ops >> GetOpt::OptionPresent('h', "help")) mode = HELP;
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
            std::cout << "-f [filename] add file to index" << std::endl
                      << "-c            clear index" << std::endl
                      << "-o            load index (used for testing - no functional purpose)" << std::endl;
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
            index = new STLHashTableIndex(indexpath);
            index->load();
/*
            std::thread threads[2];
            Index* index = new STLHashTableIndex(indexpath);
            XMLParser parser(filepath, index);

            threads[0] = std::thread([&]() {
                parser.parse();
            });
            threads[1] = std::thread([&]() {
                parser.beginProcessing();
            });
            threads[0].join();
            threads[1].join();*/
        }

        bool exit = false;
        queryprocessor* qproc = new queryprocessor(indexType);

        // enter a loop to allow the user to search index and process queries
        while (!exit) {
            char q[100];
            std::vector<std::string> processed;

            std::cout << "Please enter a search query: ";
            std::cin.getline(q, 100);
            std::string query(q);
            if (query == "exit") exit = true;
            processed = qproc->processQuery(query);
            for(std::vector<std::string>::iterator it = processed.begin(); it != processed.end(); ++it) {
                index->find(*it);
            }
        }
    } else if(mode == STRESS) {
        std::cout << "~~~ STRESS TEST MODE ~~~" << std::endl;
        std::string filepath;
        if(ops >> GetOpt::Option('f', "filename", filepath)) { // run commands
            StressTest test_it(filepath);
        } else { // show stress-test mode help

        }
    } else if(mode == HELP) {
        system("man -l ../searchengine.1");
    }

    return 0;
}

