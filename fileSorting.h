#pragma once
#include <fstream>
#include <vector>
#include "smart_pointers/uniquePointer.h"
#include "DataStructures/Sequence.h"
#include "DataStructures/ArraySequence.h"
#include "ISorter.h"
#include <iostream>

class FileSorting {
private:
    std::ifstream inputFile_;
    ArraySequence<int> ids_;
    std::vector<std::pair<int, int>> idToLine_;
    UniquePtr<ISorter<int>> sorter_;
    std::vector<int> correctLines_;
    void HeapSort();
    void MergeSort();
    void CountingSort();
    void BubbleSort();
    void collectData();
    void showData();
    static int compareInt(int a, int b) {
        if (a < b) return -1;
        if (a > b) return 1;
        return 0;
    }
public:
    FileSorting(const std::string& fileName);
    ~FileSorting();
    void sort(const std::string& sortType);
};
