// test.h
#ifndef TEST_H
#define TEST_H

#include <string>

struct PerformanceResult {
    int dataSize;
    std::string dataGenerator;
    std::string sorter;
    double averageTime;
};

void runTests();

int compareInt(int a, int b);

#endif // TEST_H
