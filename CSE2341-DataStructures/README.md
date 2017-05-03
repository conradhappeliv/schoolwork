Search Engine
-------------

Implemented by Conrad Appel and Edward Li

See man page("man -l ./searchengine.1") for specific usage instructions. More specific class information can be viewed in the Doxygen-generated documentation.

Classes:
--------

* Main: Handles parsing of command-line arguments and passing information between active classes. Main thread "manager".
* XMLParser: Uses libxml++ to parse XML file as it streams in, adding only necessary data to be parsed to a stack to be processed by the processor.
* Processor: Multi-threaded class that takes data from the parser and does necessary operations on it. Ignores any stop words, removes unnecessary punctuation, stems words, and calculates term frequencies. Sends results to the index.
* Index: interface for descendent index types with varying data structures.
* AVLIndex: Implements Index, uses an underlying AVL Tree for storage
* HashTableIndex: Implements Index, uses an underlying Hash Table (std::unordered_map) for storage
* QueryProcessor2: Parses a given query, gathers necessary information from Index, and returns a list of page IDs to caller
* StressTest: Given a test file, runs user-written commands from the file, allowing for automated usage of the search engine.
* Page.h: Page objects contain information about a specific document.

Library References:
-------------------

* getoptpp (https://code.google.com/p/getoptpp/) - used to more easily, completely, and safely gather command-line options
* Porter Stemming Algorithm (ANSI C Thread-Safe) (http://tartarus.org/~martin/PorterStemmer/) - implementation of Porter's stemming algorithm used to put words into a more general form
* libxml++ (http://libxmlplusplus.sourceforge.net/) - included TextReader interface used to stream the large XML file in and run operations on the data as it comes in from the hard drive
