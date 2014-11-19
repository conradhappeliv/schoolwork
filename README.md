Search Engine
-------------

Implemented by Conrad Appel and Edward Li

Classes:
--------

* Main: Handles parsing of command-line arguments and passing information between active classes. Main thread "manager".
* XMLParser: Uses libxml++ to parse XML file as it streams in, adding only necessary data to be parsed to a stack to be processed by the processor.
* Processor: Multi-threaded class that takes data from the parser and does necessary operations on it. Ignores any stop words, removes unnecessary punctuation, stems words, and calculates term frequencies. Sends results to the index.
* Index: interface for descendent index types with varying data structures.
* AVLIndex:
* HashTableIndex:

Library References:
-------------------

* getoptpp - https://code.google.com/p/getoptpp/
* Porter Stemming Algorithm (ANSI C Thread-Safe) - http://tartarus.org/~martin/PorterStemmer/
* libxml++ - http://libxmlplusplus.sourceforge.net/
