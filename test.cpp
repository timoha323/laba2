#include "test.h"
#include <iostream>
#include <cassert>
#include <chrono>
#include <random>
#include <vector>
#include <fstream>
#include "DataStructures/Sequence.h"
#include "DataStructures/DynamicArraySmart.h"
#include "DataStructures/LinkedListSmart.h"
#include "DataStructures/LinkedList.h"
#include "ISorter.h"
#include "HeapSorter.h"
#include "MergeSorter.h"
#include "BubbleSorter.h"
#include "CountingSorter.h"
#include "DataStructures/ArraySequence.h"

namespace {

enum class DataType {
    RANDOM,
    REVERSE,
    PARTIAL_SORTED,
    ALREADY_SORTED,
    EMPTY
};

struct GeneratorInfo {
    std::string name;
    DataType type;
    int sortedElements;
};

struct TestScenario {
    std::string description;
    std::vector<int> data;
};

struct SorterInfo {
    std::string name;
    ISorter<int>* sorter;
};

struct SequenceInfo {
    std::string name;
    Sequence<int>* (*createSequence)(const int*, int);
};

template <typename T>
bool isSorted(Sequence<T>* seq, int (*cmp)(T, T)) {
    for (int i = 1; i < seq->GetLength(); ++i) {
        if (cmp(seq->Get(i - 1), seq->Get(i)) > 0) {
            return false;
        }
    }
    return true;
}

std::vector<int> generateData(int size, DataType type, int sortedElements = 0) {
    std::vector<int> data;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    switch (type) {
        case DataType::RANDOM:
            for (int i = 0; i < size; ++i) {
                data.push_back(dis(gen));
            }
        break;
        case DataType::REVERSE:
            for (int i = 0; i < size; ++i) {
                data.push_back(size - i);
            }
        break;
        case DataType::PARTIAL_SORTED:
            for (int i = 0; i < sortedElements && i < size; ++i) {
                data.push_back(i);
            }
            for (int i = sortedElements; i < size; ++i) {
                data.push_back(dis(gen));
            }
        break;
        case DataType::ALREADY_SORTED:
            for (int i = 0; i < size; ++i) {
                data.push_back(i);
            }
        break;
        case DataType::EMPTY:
            break;
    }

    return data;
}

} // namespace

int compareInt(int a, int b) {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

void runFunctionalTests() {
    std::cout << "Running functional tests...\n";

    std::vector<TestScenario> testScenarios = {
        {"Random data", {5, 3, 8, 1, 9, 2}},
        {"Reverse sorted data", {9, 8, 7, 6, 5, 4, 3, 2, 1}},
        {"Partially sorted data (1 element sorted)", {1, 3, 8, 6, 5, 2}},
        {"Partially sorted data (2 elements sorted)", {1, 2, 8, 6, 5, 3}},
        {"Partially sorted data (3 elements sorted)", {1, 2, 3, 6, 5, 4}},
        {"Already sorted data", {1, 2, 3, 4, 5, 6}},
        {"Empty data", {}}
    };

    std::vector<SorterInfo> sorters = {
        {"HeapSorter", new HeapSorter<int>()},
        {"MergeSorter", new MergeSorter<int>()},
        {"BubbleSorter", new BubbleSorter<int>()}
    };

    std::vector<SequenceInfo> sequences = {
        {"ArraySequence", [](const int* data, int size) -> Sequence<int>* {
            return new DynamicArraySmart<int>(data, size);
        }},
        {"ListSequence", [](const int* data, int size) -> Sequence<int>* {
            return new LinkedListSmart<int>(data, size);
        }}
    };

    for (const auto& scenario : testScenarios) {
        std::cout << "Testing: " << scenario.description << "\n";

        for (const auto& seqInfo : sequences) {
            for (const auto& sorterInfo : sorters) {

                Sequence<int>* seq = nullptr;
                if (scenario.data.empty()) {
                    seq = seqInfo.createSequence(nullptr, 0);
                } else {
                    seq = seqInfo.createSequence(scenario.data.data(), scenario.data.size());
                }

                sorterInfo.sorter->sort(*seq, compareInt);

                if (scenario.data.empty()) {
                    assert(seq->GetLength() == 0 && "Sorted empty sequence should have length 0.");
                } else {
                    assert(isSorted(seq, compareInt) && "Sequence is not sorted correctly.");
                }

                delete seq;
            }
        }
    }

    for (const auto& sorterInfo : sorters) {
        delete sorterInfo.sorter;
    }

    std::cout << "Functional tests passed.\n";
}

void runPerformanceTests(const int& size) {
    std::cout << "Running performance tests...\n";
    std::vector<int> sizes = {20000, 40000, 60000, 80000, 100000};
    if (size < 0) {
        std::cout << "Size must be positive.\n";
        return;
    }
    if(size) {
        sizes = {size, size*2, size*4, size*8, size*16};
    }

    std::vector<GeneratorInfo> generators = {
        {"Random", DataType::RANDOM, 0},
        {"Reverse Sorted", DataType::REVERSE, 0},
        {"Partially Sorted (1 sorted)", DataType::PARTIAL_SORTED, 1},
        {"Partially Sorted (2 sorted)", DataType::PARTIAL_SORTED, 2},
        {"Partially Sorted (3 sorted)", DataType::PARTIAL_SORTED, 3},
        {"Already Sorted", DataType::ALREADY_SORTED, 0},
        {"Empty", DataType::EMPTY, 0}
    };

    std::vector<SorterInfo> sorters = {
        {"HeapSorter", new HeapSorter<int>()},
        {"MergeSorter", new MergeSorter<int>()},
        {"CountingSorter", new CountingSorter<int>()},
        {"BubbleSorter", new BubbleSorter<int>()}
    };

    std::vector<SequenceInfo> sequences = {
        {"ArraySequence", [](const int* data, int size) -> Sequence<int>* {
            return new DynamicArraySmart<int>(data, size);
        }}
    };

    struct PerformanceResult {
        int dataSize;
        std::string dataGenerator;
        std::string sorter;
        double averageTime;
    };

    std::vector<PerformanceResult> performanceResults;

    for (int size : sizes) {
        std::cout << "\nData Size: " << size << " elements\n";
        for (const auto& genInfo : generators) {
            if (genInfo.type == DataType::EMPTY && size != 0) continue;
            std::cout << "  Data Generator: " << genInfo.name << "\n";
            for (const auto& seqInfo : sequences) {
                for (const auto& sorterInfo : sorters) {
                    double totalTime = 0.0;
                    std::vector<int> data = generateData(size, genInfo.type, genInfo.sortedElements);

                    Sequence<int>* seq = nullptr;
                    if (data.empty()) {
                        seq = seqInfo.createSequence(nullptr, 0);
                    } else {
                        seq = seqInfo.createSequence(data.data(), data.size());
                    }
                    if (size >= 10000 && sorterInfo.name == "BubbleSorter") {
                        std::cout << "\nToo much for bubble sort\n";
                        continue;
                    }
                    auto start = std::chrono::high_resolution_clock::now();
                    sorterInfo.sorter->sort(*seq, compareInt);
                    auto end = std::chrono::high_resolution_clock::now();
                    if (data.empty()) {
                        assert(seq->GetLength() == 0 && "Sorted empty sequence should have length 0.");
                    } else {
                        assert(isSorted(seq, compareInt) && "Sequence is not sorted correctly.");
                    }
                    std::chrono::duration<double> duration = end - start;
                    totalTime += duration.count();
                    delete seq;

                    double averageTime = totalTime;
                    performanceResults.push_back({size, genInfo.name, sorterInfo.name, averageTime});
                    std::cout << "    " << sorterInfo.name << " with ArraySequence: "
                              << averageTime << " seconds\n";
                }
            }
        }
    }

    std::ofstream csvFile("performance_results.csv");
    csvFile << "Data Size,Data Generator,Sorter,Average Time (seconds)\n";

    for (const auto& result : performanceResults) {
        csvFile << result.dataSize << ","
                << result.dataGenerator << ","
                << result.sorter << ","
                << std::fixed << std::setprecision(6) << result.averageTime << "\n";
    }

    csvFile.close();
    std::cout << "\nResults saved to 'performance_results.csv'.\n";

    for (const auto& sorterInfo : sorters) {
        delete sorterInfo.sorter;
    }

    if (system("python3 ../py_script.py")) {
        std::cout << "Graphics created successfully\n";
    }
    std::cout << "\nPerformance tests completed.\n";
}

void runTests() {
    int size;
    std::cout << "\nENTER SIZE FOR TEST DATA (if u can't imagine enter 0)\nP.S. it will be doubled five times\n";
    std::cin >> size;
    runFunctionalTests();
    runPerformanceTests(size);
}
