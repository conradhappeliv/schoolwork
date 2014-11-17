#include <iostream>
#include <thread>
#include <stack>

#include "lib/getopt_pp.h"
#include "src/xmlparser.h"
#include "src/index.h"
#include "src/processor.h"

enum modes {
    MAINTENANCE,
    INTERACTIVE,
    STRESS,
    HELP
};
enum indextype {
    AVLTREE,
    HASHTABLE
};

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
            std::thread threads[2];
            XMLParser parser(filepath);
            Processor processor;

            threads[0] = std::thread([&]() {
                parser.parse();
            });
            threads[1] = std::thread([&]() {
                parser.setProcessor(processor);
            });
            threads[0].join();
            threads[1].join();
        } else if(ops >> GetOpt::OptionPresent('c', "clear")){ // clear index

        } else { // show help relevant to maintenance mode

        }
    } else if(mode == INTERACTIVE) {
        std::cout << "~~~ INTERACTIVE MODE ~~~" << std::endl;
        int indexType = AVLTREE; // default index type
        if(ops >> GetOpt::OptionPresent('a', "avltree")) indexType = AVLTREE;
        else if(ops >> GetOpt::OptionPresent('t', "hashtable")) indexType = HASHTABLE;
        while(true) { // enter a loop to allow the user to search index
            std::cout << "infinite loop";
        }
    } else if(mode == STRESS) {
        std::cout << "~~~ STRESS TEST MODE ~~~" << std::endl;
        std::string filepath;
        if(ops >> GetOpt::Option('f', "filename", filepath)) { // run commands

        } else { // show stress-test mode help

        }
    } else if(mode == HELP) {
        std::cout << "~~~ HELP ~~~" << std::endl;

    }

    return 0;
}

