Search Engine
Performance Report
----------

Implemented by Conrad Appel and Edward Li

----------
README
----------

Open ~/html/index.html to see Search Engine Doxygen-generated documentation.

All additional information can be found at the following links:
http://github.com/edjli2005/semproj-14
(personal Github repo used for development)

http://github.com/SMUCSE2341/ELi/tree/master/Project5
(code imported into class repo)

See README for basic class descriptions and references to outside libraries implemented in this project.

See man page("man -l ./searchengine.1") for specific usage instructions. More specific class information can be viewed in the Doxygen-generated documentation.


----------
REPORT
----------

The stress test mode tests the time requred to open the index file, load the index data into a data structure in memory, save, and close the index. 

Stress Test Routine: (see manpage for more details)
ST
HT/AV (depending on which data structure being tested)
OP /home/edward/Desktop/semproj-14/default.index (directory of index file)
CL
EN

Hash Table Timer Values (full wikibooks dump):
Test 1: 53.197 seconds
Test 2: 51.476 seconds
Test 3: 41.013 seconds
Test 4: 38.093 seconds
Test 5: 45.578 seconds
Avg. Time: 45.8714 seconds

AVL Tree Timer Values (full wikibooks dump):
Test 1: 45.703 seconds
Test 2: 38.071 seconds
Test 3: 36.661 seconds
Test 4: 36.867 seconds
Test 5: 36.122 seconds
Avg. Time: 38.6848 seconds

Which one is better?
The AVL Tree implementation performs better. This is quantifiable by the results as displayed above for the timings of the full wikibooks xml file. The performance increase of the AVL tree can be attributed to its big-O complexity for search and insertion being O(log(n)) versus O(1) of the hash table. The data set is not large enough for the time taken by the AVL Tree to fully converge on constant time of the Hash Table. When testing with a small data set of about 500 documents (on organic chemistry and data structures topics only), the timing differences seen between the two are negligible but still noticeable. The AVL Tree timing value comes in around 38 milliseconds while the Hash Table takes about 45 milliseconds.
