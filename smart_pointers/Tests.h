#pragma once
#include <string>
#include <set>
#include <mutex>

class Tests {
private:
    std::set<std::string> testOutput;
    std::mutex testOutputMutex;

    template<typename Func>
    void measureTime(const std::string& description, Func f);
    void testSharedPointerPerformance(size_t numElements);
    void testUniquePointerPerformance(size_t numElements);
    void testPointerPerformance(size_t numElements);
    void runTestsShared();
    void runTestsUnique();
    void runTestsPointers();

public:
    void RunAllTests();
};
