#ifndef STRESSTEST_H
#define STRESSTEST_H

#include <chrono>
#include <fstream>

class StressTest
{
public:
    /// pass in a filename of a test to run
    StressTest(std::string);
private:
    enum index_types {
        HASHTABLE,
        AVLTREE
    };
    /// set in ST function, used to calculate stopwatch differences
    std::chrono::time_point<std::chrono::system_clock> start;
    /// set in EN function, used to calculate stopwatch differences
    std::chrono::time_point<std::chrono::system_clock> stop;
    /// flag to make sure only one stopwatch is set
    bool timer_running = false;
    /// flag to make sure index is in a usable state
    bool index_open = false;
    /// flag to track whether the index has unsaved changes
    bool index_changed = false;
    int index_type = HASHTABLE;
};

#endif // STRESSTEST_H
