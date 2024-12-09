#include "fileSorting.h"
#include "HeapSorter.h"
#include "BubbleSorter.h"
#include "BubbleSorter.h"
#include "MergeSorter.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "CountingSorter.h"

FileSorting::FileSorting(const std::string& fileName) {
    inputFile_.open(fileName);
    if (!inputFile_.is_open()) {
        std::cerr << "Error opening file " << fileName << std::endl;
        throw "Error opening file";
    }
}

FileSorting::~FileSorting() {
    inputFile_.close();
}

void FileSorting::showData() {
    for (int i = 0; i < idToLine_.size(); ++i) {
        for (const auto& [id, line] : idToLine_) {
            if(ids_.Get(i) == id) {
                correctLines_.push_back(line);
            }
        }
    }
    std::string line;
    std::ofstream outputFile_("output.txt");
    int i = 0;
    for (int j = 0; j < correctLines_.size(); ++j) {
        while (std::getline(inputFile_, line)) {
            if (correctLines_[j] == i) {
                outputFile_ << line << "\n";
            }
            ++i;
        }
    }
    outputFile_.close();
}

void FileSorting::HeapSort() {
    sorter_ = UniquePtr<ISorter<int>>(new HeapSorter<int>());
    sorter_->sort(ids_, compareInt);
    showData();
}
void FileSorting::MergeSort() {
    sorter_ = UniquePtr<ISorter<int>>(new MergeSorter<int>());
    sorter_->sort(ids_, compareInt);
    showData();
}
void FileSorting::BubbleSort() {
    sorter_ = UniquePtr<ISorter<int>>(new BubbleSorter<int>());
    sorter_->sort(ids_, compareInt);
    showData();
}

void FileSorting::CountingSort() {
    sorter_ = UniquePtr<ISorter<int>>(new CountingSorter<int>());
    sorter_->sort(ids_, compareInt);
    showData();
}


void FileSorting::collectData() {
    std::string line;
    int i = 0;
    while (std::getline(inputFile_, line)) {
        std::istringstream iss(line);
        std::string lastName, firstName, patronymic, birthDate;
        int id;
        if (iss >> lastName >> firstName >> patronymic >> birthDate >> id) {
            ids_.Append(id);
            idToLine_.emplace_back(id, i);
        }
        ++i;
    }
}

void FileSorting::sort(const std::string& sortType) {
    collectData();
    if (sortType == "HeapSort") {
        HeapSort();
    } else if (sortType == "MergeSort") {
        MergeSort();
    } else if (sortType == "CountingSort") {
        CountingSort();
    } else if (sortType == "BubbleSort") {
        BubbleSort();
    } else {
        std::cerr << "Неизвестный тип сортировки: " << sortType << std::endl;
    }
}
