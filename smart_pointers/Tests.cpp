#include "Tests.h"
#include "sharedPointer.h"
#include "uniquePointer.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
//проверка подсчета кол-ва созданных тестовых обхектов
class Counter {
    static int counterObjects;

};

template<typename Func>
void Tests::measureTime(const std::string& description, Func f) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::string localOutput = description + ": " + std::to_string(duration.count()) + " seconds";
    std::scoped_lock<std::mutex> lock(testOutputMutex);
    testOutput.insert(localOutput);
}

void Tests::testSharedPointerPerformance(size_t numElements) {
    measureTime("Created " + std::to_string(numElements) + " elements SHARED", [numElements]() {
        std::vector<SharedPointer<int>> pointers;
        for (size_t i = 0; i < numElements; ++i) {
            pointers.push_back(SharedPointer<int>(new int(i)));
        }
    });

    measureTime("Copied " + std::to_string(numElements) + " elements SHARED", [numElements]() {
        std::vector<SharedPointer<int>> pointers;
        for (size_t i = 0; i < numElements; ++i) {
            pointers.push_back(SharedPointer<int>(new int(i)));
        }
        std::vector<SharedPointer<int>> copiedPointers = pointers;
    });
}

void Tests::testUniquePointerPerformance(size_t numElements) {
    measureTime("Created " + std::to_string(numElements) + " elements UNIQUE", [numElements]() {
        std::vector<UniquePtr<int>> pointers;
        for (size_t i = 0; i < numElements; ++i) {
            pointers.push_back(UniquePtr<int>(new int(i)));
        }
    });

    measureTime("Moved " + std::to_string(numElements) + " elements UNIQUE", [numElements]() {
        std::vector<UniquePtr<int>> pointers;
        for (size_t i = 0; i < numElements; ++i) {
            pointers.push_back(UniquePtr<int>(new int(i)));
        }
        std::vector<UniquePtr<int>> movedPointers = std::move(pointers);
    });
}

void Tests::testPointerPerformance(size_t numElements) {
    measureTime("Created " + std::to_string(numElements) + " elements DEFAULT", [numElements]() {
        std::vector<int*> pointers;
        for (size_t i = 0; i < numElements; ++i) {
            pointers.push_back(new int(i));
        }
        for (size_t i = 0; i < numElements; ++i) {
            delete pointers[i];
        }
    });

    measureTime("Copied " + std::to_string(numElements) + " elements DEFAULT", [numElements]() {
        std::vector<int*> pointers;
        for (size_t i = 0; i < numElements; ++i) {
            pointers.push_back(new int(i));
        }
        std::vector<int*> copiedPointers = pointers;
        for (size_t i = 0; i < numElements; ++i) {
            delete pointers[i];
        }
    });
}

void Tests::runTestsShared() {
    std::thread testThread1([this]() { testSharedPointerPerformance(100); });
    std::thread testThread2([this]() { testSharedPointerPerformance(100000); });
    std::thread testThread3([this]() { testSharedPointerPerformance(10'000'000); });

    testThread1.join();
    testThread2.join();
    testThread3.join();
}

void Tests::runTestsUnique() {
    std::thread testThread1([this]() { testUniquePointerPerformance(100); });
    std::thread testThread2([this]() { testUniquePointerPerformance(100000); });
    std::thread testThread3([this]() { testUniquePointerPerformance(10'000'000); });

    testThread1.join();
    testThread2.join();
    testThread3.join();
}

void Tests::runTestsPointers() {
    std::thread testThread1([this]() { testPointerPerformance(100); });
    std::thread testThread2([this]() { testPointerPerformance(100000); });
    std::thread testThread3([this]() { testPointerPerformance(10'000'000); });

    testThread1.join();
    testThread2.join();
    testThread3.join();
}

void Tests::RunAllTests() {
    std::thread testThread1([this]() { runTestsShared(); });
    std::thread testThread2([this]() { runTestsUnique(); });
    std::thread testThread3([this]() { runTestsPointers(); });

    testThread1.join();
    testThread2.join();
    testThread3.join();

    for(const auto& output : testOutput) {
        std::cout << output << std::endl;
    }
}
