// Owner: Conrad Appel

#include "stresstest.h"
#include "index.h"
#include "stlhashtableindex.h"
#include "avltreeindex.h"
#include "xmlparser.h"

#include <iostream>
#include <sstream>

StressTest::StressTest(std::string filename) {
    std::ifstream inFile(filename);
    if(!inFile.is_open()) throw;

    std::string line, opcode;
    Index* index;
    while(inFile.good()) {
        line = opcode = "";
        std::getline(inFile, line);
        std::stringstream line_stream(line);
        line_stream >> opcode;
        if(opcode == "ST") { // start timer
            if(timer_running) std::cout << "Timer already running." << std::endl;
            else {
                start = std::chrono::system_clock::now();
                timer_running = true;
                std::cout << "Timer started." << std::endl;
            }
        }
        else if(opcode == "EN") { // end timer, output time between
            if(!timer_running) std::cout << "Timer not running." << std::endl;
            else {
                stop = std::chrono::system_clock::now();
                auto diff = stop - start;
                auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
                auto s = std::chrono::duration_cast<std::chrono::seconds>(diff).count();
                std::cout << "Timer stopped: " << (int) ms/1000 << " seconds, " << (int)ms%1000 << " milliseconds" << std::endl;
                timer_running = false;
            }
        }
        else if(opcode == "CL") { // close/save index
            if(!index_open) std::cout << "No index open. Can't save/close." << std::endl;
            else {
                index->save();
                delete index;
                index_open = false;
                index_changed = false;
                std::cout << "Index saved and closed." << std::endl;
            }
        }
        else if(opcode == "OP") { // open index
            if(index_open) std::cout << "Index already open. Can't open another." << std::endl;
            else {
                std::string index_filename;
                line_stream >> index_filename;
                if(index_type == HASHTABLE) index = new STLHashTableIndex(index_filename);
                else if(index_type == AVLTREE) index = new AVLTreeIndex(index_filename);
                else throw; // something wrong happened
                index->load();
                index_open = true;
                index_changed = false;
                std::cout << "Index successfully loaded." << std::endl;
            }
        }
        else if(opcode == "RM") { // clear index
            if(!index_open) std::cout << "No index open. Can't clear." << std::endl;
            else {
                index->clear();
                std::cout << "Index cleared." << std::endl;
                index_changed = true;
            }
        }
        else if(opcode == "LD") { // load file into index
            if(!index_open) std::cout << "No index open to add to" << std::endl;
            else {
                std::string filename;
                line_stream >> filename;
                XMLParser parser(filename, index);
                parser.threadedParseAndProcess();
                std::cout << filename <<" loaded into index." << std::endl;
                index_changed = true;
            }
        }
        else if(opcode == "QU") { // run query on index
            if(!index_open) std::cout << "No index open to query." << std::endl;
            else {
                line.erase(0, 3); // just keep query from here on out
                // TODO
            }
        }
        else if(opcode == "AV") { // select avl tree
            if(index_open) {
                std::cout << "Can't select AVL Tree. Index in use already!" << std::endl;
            } else {
                index_type = AVLTREE;
                std::cout << "Index type set to AVL Tree." << std::endl;
            }
        }
        else if(opcode == "HT") { // select hash table
            if(index_open) {
                std::cout << "Can't select Hash table. Index in use already!" << std::endl;
            } else {
                index_type = HASHTABLE;
                std::cout << "Index type set to Hash Table." << std::endl;
            }
        }
        else if(opcode == "PN") { // retrieve page number
            if(!index_open) std::cout << "No index open to retrieve from." << std::endl;
            else {
                unsigned int id;
                line_stream >> id;
                std::cout << "Page ID " << id << ": " << index->IDtoTitle(id) << std::endl;
            }
        }
    }

    // save changes
    if(index_open && index_changed) {
        char ans;
        std::cout << std::endl << "Do you want to save changes to the index? (y/n): ";
        ans = std::cin.get();
        if(ans == 'y') {
            index->save();
        }
    }
}
