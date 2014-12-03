#ifndef STRESSTEST_H
#define STRESSTEST_H

#include <chrono>
#include <fstream>

class StressTest
{
public:
    StressTest(std::string);
private:
    enum index_types {
        HASHTABLE,
        AVLTREE
    };
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> stop;
    bool timer_running = false;
    bool index_open = false;
    bool index_changed = false;
    int index_type = HASHTABLE;
};

#endif // STRESSTEST_H
