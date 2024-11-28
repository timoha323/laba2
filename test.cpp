#include "test.h"
#include <iostream>
#include <cassert>
#include <chrono>
#include <random>
#include <vector>
#include "DataStructures/Sequence.h"
#include "DataStructures/DynamicArraySmart.h"
#include "DataStructures/LinkedListSmart.h"
#include "DataStructures/LinkedList.h"
#include "ISorter.h"
#include "HeapSorter.h"
#include "MergeSorter.h"
#include "BubbleSorter.h"
#include "CountingSorter.h"

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
    LinkedList<int> data;
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

LinkedList<int> generateData(int size, DataType type, int sortedElements = 0) {
    LinkedList<int> data;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    switch (type) {
        case DataType::RANDOM:
            for (int i = 0; i < size; ++i) {
                data.Append(dis(gen));
            }
        break;
        case DataType::REVERSE:
            for (int i = 0; i < size; ++i) {
                data.Append(size - i);
            }
        break;
        case DataType::PARTIAL_SORTED:
            for (int i = 0; i < sortedElements && i < size; ++i) {
                data.Append(i);
            }
        for (int i = sortedElements; i < size; ++i) {
            data.Append(dis(gen));
        }
        break;
        case DataType::ALREADY_SORTED:
            for (int i = 0; i < size; ++i) {
                data.Append(i);
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

    LinkedList<TestScenario> testScenarios;
    testScenarios.Append({"Random data", LinkedList<int>()});
    testScenarios.Append({"Reverse sorted data", LinkedList<int>()});
    testScenarios.Append({"Partially sorted data (1 element sorted)", LinkedList<int>()});
    testScenarios.Append({"Partially sorted data (2 elements sorted)", LinkedList<int>()});
    testScenarios.Append({"Partially sorted data (3 elements sorted)", LinkedList<int>()});
    testScenarios.Append({"Already sorted data", LinkedList<int>()});
    testScenarios.Append({"Empty data", LinkedList<int>()});

    testScenarios[0].data.Append(5);
    testScenarios[0].data.Append(3);
    testScenarios[0].data.Append(8);
    testScenarios[0].data.Append(1);
    testScenarios[0].data.Append(9);
    testScenarios[0].data.Append(2);

    testScenarios[1].data.Append(9);
    testScenarios[1].data.Append(8);
    testScenarios[1].data.Append(7);
    testScenarios[1].data.Append(6);
    testScenarios[1].data.Append(5);
    testScenarios[1].data.Append(4);
    testScenarios[1].data.Append(3);
    testScenarios[1].data.Append(2);
    testScenarios[1].data.Append(1);

    testScenarios[2].data.Append(1);
    testScenarios[2].data.Append(3);
    testScenarios[2].data.Append(8);
    testScenarios[2].data.Append(6);
    testScenarios[2].data.Append(5);
    testScenarios[2].data.Append(2);

    testScenarios[3].data.Append(1);
    testScenarios[3].data.Append(2);
    testScenarios[3].data.Append(8);
    testScenarios[3].data.Append(6);
    testScenarios[3].data.Append(5);
    testScenarios[3].data.Append(3);

    testScenarios[4].data.Append(1);
    testScenarios[4].data.Append(2);
    testScenarios[4].data.Append(3);
    testScenarios[4].data.Append(6);
    testScenarios[4].data.Append(5);
    testScenarios[4].data.Append(4);

    testScenarios[5].data.Append(1);
    testScenarios[5].data.Append(2);
    testScenarios[5].data.Append(3);
    testScenarios[5].data.Append(4);
    testScenarios[5].data.Append(5);
    testScenarios[5].data.Append(6);

    testScenarios[6].data.Clear();

    LinkedList<SorterInfo> sorters;
    sorters.Append({"HeapSorter", new HeapSorter<int>()});
    sorters.Append({"MergeSorter", new MergeSorter<int>()});
    sorters.Append({"BubbleSorter", new BubbleSorter<int>()});

    LinkedList<SequenceInfo> sequences;
    sequences.Append({"ArraySequence", [](const int* data, int size) -> Sequence<int>* {
        return new DynamicArraySmart <int>(data, size);
    }});
    sequences.Append({"ListSequence", [](const int* data, int size) -> Sequence<int>* {
        return new LinkedListSmart<int>(data, size);
    }});

    for (auto scenarioIt = testScenarios.begin(); scenarioIt != testScenarios.end(); ++scenarioIt) {
        const auto& scenario = *scenarioIt;
        std::cout << "Testing: " << scenario.description << "\n";

        for (auto seqInfoIt = sequences.begin(); seqInfoIt != sequences.end(); ++seqInfoIt) {
            const auto& seqInfo = *seqInfoIt;
            for (auto sorterIt = sorters.begin(); sorterIt != sorters.end(); ++sorterIt) {
                const auto& sorterInfo = *sorterIt;

                Sequence<int>* seq = nullptr;
                if (scenario.data.GetLength() == 0) {
                    seq = seqInfo.createSequence(nullptr, 0);
                } else {
                    int* dataArray = new int[scenario.data.GetLength()];
                    int i = 0;
                    for (auto it = scenario.data.begin(); it != scenario.data.end(); ++it) {
                        dataArray[i++] = *it;
                    }
                    seq = seqInfo.createSequence(dataArray, scenario.data.GetLength());
                    delete[] dataArray;
                }

                sorterInfo.sorter->sort(seq, compareInt);

                if (scenario.data.GetLength() == 0) {
                    assert(seq->GetLength() == 0 && "Sorted empty sequence should have length 0.");
                } else {
                    assert(isSorted(seq, compareInt) && "Sequence is not sorted correctly.");
                }

                delete seq;
            }
        }
    }

    for (auto sorterIt = sorters.begin(); sorterIt != sorters.end(); ++sorterIt) {
        delete sorterIt->sorter;
    }

    std::cout << "Functional tests passed.\n";
}

void runPerformanceTests() {
    std::cout << "Running performance tests...\n";
    LinkedList<int> sizes;

    sizes.Append(10000);
    sizes.Append(50000);
    sizes.Append(100000);

    LinkedList<GeneratorInfo> generators;

    generators.Append({"Random", DataType::RANDOM, 0});
    generators.Append({"Reverse Sorted", DataType::REVERSE, 0});
    generators.Append({"Partially Sorted (1 sorted)", DataType::PARTIAL_SORTED, 1});
    generators.Append({"Partially Sorted (2 sorted)", DataType::PARTIAL_SORTED, 2});
    generators.Append({"Partially Sorted (3 sorted)", DataType::PARTIAL_SORTED, 3});
    generators.Append({"Already Sorted", DataType::ALREADY_SORTED, 0});
    generators.Append({"Empty", DataType::EMPTY, 0});

    LinkedList<SorterInfo> sorters;

    sorters.Append({"HeapSorter", new HeapSorter<int>()});
    sorters.Append({"MergeSorter", new MergeSorter<int>()});
    sorters.Append({"BubbleSorter", new BubbleSorter<int>()});
    sorters.Append({"CountingSorter", new CountingSorter<int>()});

    LinkedList<SequenceInfo> sequences;

    sequences.Append({"ArraySequence", [](const int* data, int size) -> Sequence<int>* {
        return new DynamicArraySmart<int>(data, size);
    }});

    LinkedList<PerformanceResult> performanceResults;

    for (auto sizeIt = sizes.begin(); sizeIt != sizes.end(); ++sizeIt) {
        int size = *sizeIt;
        std::cout << "\nData Size: " << size << " elements\n";
        for (auto& genInfo : generators) {
            if (genInfo.type == DataType::EMPTY && size != 0) continue;
            std::cout << "  Data Generator: " << genInfo.name << "\n";
            for (auto& seqInfo : sequences) {
                for (auto& sorterInfo : sorters) {
                    double totalTime = 0.0;

                    LinkedList<int> data = generateData(size, genInfo.type, genInfo.sortedElements);
                    Sequence<int>* seq = nullptr;
                    if (data.GetLength() == 0) {
                        seq = seqInfo.createSequence(nullptr, 0);
                    } else {
                        int* dataArray = new int[data.GetLength()];
                        int i = 0;
                        for (auto it = data.begin(); it != data.end(); ++it) {
                            dataArray[i++] = *it;
                        }
                        seq = seqInfo.createSequence(dataArray, data.GetLength());
                        delete[] dataArray;
                    }
                    auto start = std::chrono::high_resolution_clock::now();
                    sorterInfo.sorter->sort(seq, compareInt);
                    auto end = std::chrono::high_resolution_clock::now();
                    if (!data.GetLength()) {
                        assert(seq->GetLength() == 0 && "Sorted empty sequence should have length 0.");
                    } else {
                        assert(isSorted(seq, compareInt) && "Sequence is not sorted correctly.");
                    }
                    std::chrono::duration<double> duration = end - start;
                    totalTime += duration.count();
                    delete seq;

                    double averageTime = totalTime;
                    performanceResults.Append({size, genInfo.name, sorterInfo.name, averageTime});
                    std::cout << "    " << sorterInfo.name << " with ArraySequence: "
                              << averageTime << " seconds\n\n";
                }
            }
        }
    }
    for (auto& sorterInfo : sorters) {
        delete sorterInfo.sorter;
    }

    std::cout << "\nPerformance tests completed.\n";
}

void runTests() {
    runFunctionalTests();
    runPerformanceTests();
}
