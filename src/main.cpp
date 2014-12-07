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
        std::cout << "Loading " << indexpath;
        std::flush(std::cout);
        index->load();
        std::cout << "\r";
        std::flush(std::cout);

        queryprocessor2 query_me(index);

        // enter a loop to allow the user to search index and process queries
        while (true) {
            char q[100000];

            std::cout << "Please enter a search query, \"retrieve[all] [page_id]\", or \"exit\": ";
            std::cin.getline(q, 100000);
            std::string query(q);
            if (query == "exit") break;
            else if(query.compare(0, 8, "retrieve") == 0) {
                bool all = false;
                unsigned int offset = 9;
                if(query.compare(8, 3, "all") == 0) {
                    all = true;
                    offset += 3;
                }
                std::string display_me = "";

                unsigned int page_id = std::atoi(query.substr(offset, std::string::npos).c_str());
                try {
                    const Page* page = index->IDtoPage(page_id);
                    display_me += "\n----------\n";
                    display_me += page->title + '\n';
                    display_me += "Posted on " + page->date + " by " + page->username + '\n';
                    display_me += "----------\n";
                    display_me += page->body;
                } catch (std::invalid_argument) {
                    std::cout << "Page not in index" << std::endl;
                    continue;
                }
                if(!all && display_me.length() > 4096) {
                    display_me.erase(4096);
                    std::cout << display_me << std::endl;
                    std::cout << std::endl << "------------------------------------" << std::endl;
                    std::cout << "Type \"retrieveall " << page_id << "\" to see the entire contents." << std::endl;
                } else if(all) {
                    char* temp_filename = "./temp";
                    std::ofstream temp_file(temp_filename);
                    temp_file << display_me;
                    temp_file.close();
                    system("less ./temp");
                    remove(temp_filename);
                } else std::cout << display_me << std::endl;
            } else {
                auto results = query_me.processQuery(query);
                if(results.size() == 0) std::cout << "No results." << std::endl;
                for(auto it = results.begin(); it != results.end(); it++) {
                    std::cout << *it << ": " << index->IDtoTitle(*it) << std::endl;
                }
                std::cout << std::endl << std::endl;
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

