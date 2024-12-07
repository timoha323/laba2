#include "interface.h"
#include <iostream>
#include <random>
#include <chrono>
#include <limits>
#include <exception>
#include <thread>
#include <mutex>
#include <future>
#include "BubbleSorter.h"
#include "test.h"
#include "DataStructures/Sequence.h"
#include "DataStructures/ArraySequence.h"
#include "DataStructures/ListSequence.h"
#include "ISorter.h"
#include "HeapSorter.h"
#include "MergeSorter.h"
#include "BubbleSorter.h"
#include "CountingSorter.h"
#include "smart_pointers/uniquePointer.h"

namespace {

constexpr int MAX_PRINT = 40;

int getValidatedInt(const std::string &prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        } else {
            std::cout << "Invalid input. Please enter an integer value.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int getValidatedIntInRange(const std::string &prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        value = getValidatedInt(prompt);
        if (value >= minValue && value <= maxValue) {
            return value;
        } else {
            std::cout << "Invalid choice. Please enter a number between " << minValue << " and " << maxValue << ".\n";
        }
    }
}

int getValidatedPositiveInt(const std::string &prompt) {
    int value;
    while (true) {
        value = getValidatedInt(prompt);
        if (value > 0) {
            return value;
        } else {
            std::cout << "Please enter a positive integer.\n";
        }
    }
}

} ///namespace

void runInterface() {
    int choice;
    do {
        std::cout << "==== Sorting Algorithms ====\n";
        std::cout << "1. Heap Sort\n";
        std::cout << "2. Merge Sort\n";
        std::cout << "3. Bubble Sort\n";
        std::cout << "4. Counting Sort\n";
        std::cout << "5. Tests\n";
        std::cout << "0. Exit\n";
        choice = getValidatedIntInRange("Select choice: ", 0, 5);

        if (choice == 0) {
            break;
        } else if (choice == 5) {
            runTests();
            continue;
        }

        UniquePtr<ISorter<int>> sorter;
        switch (choice) {
            case 1:
                sorter = UniquePtr<ISorter<int>>(new HeapSorter<int>());
                break;
            case 2:
                sorter = UniquePtr<ISorter<int>>(new MergeSorter<int>());
                break;
            case 3:
                sorter = UniquePtr<ISorter<int>>(new BubbleSorter<int>());
                break;
            case 4:
                sorter = UniquePtr<ISorter<int>>(new CountingSorter<int>());
                break;
            default:
                continue;
        }

        std::cout << "Select sequence type:\n";
        std::cout << "1. ArraySequence\n";
        std::cout << "2. ListSequence\n";
        int seqType = getValidatedIntInRange("Choice: ", 1, 2);

        UniquePtr<Sequence<int>> seq;
        if (seqType == 1) {
            seq = UniquePtr<Sequence<int>>(new ArraySequence<int>());
        } else if (seqType == 2) {
            seq = UniquePtr<Sequence<int>>(new ListSequence<int>());
        } else {
            continue;
        }

        std::cout << "Data input options:\n";
        std::cout << "1. Enter data manually\n";
        std::cout << "2. Generate random data\n";
        int dataChoice = getValidatedIntInRange("Choice: ", 1, 2);

        if (dataChoice == 1) {
            int n = getValidatedPositiveInt("Enter number of elements: ");
            std::cout << "Enter elements:\n";
            for (int i = 0; i < n; ++i) {
                int val = getValidatedInt("Element " + std::to_string(i + 1) + ": ");
                seq->Append(val);
            }
        } else if (dataChoice == 2) {
            int n = getValidatedPositiveInt("Enter number of elements: ");
            int minVal = getValidatedInt("Enter minimum value: ");
            int maxVal;
            while (true) {
                maxVal = getValidatedInt("Enter maximum value: ");
                if (maxVal >= minVal) {
                    break;
                } else {
                    std::cout << "Maximum value must be greater than or equal to minimum value.\n";
                }
            }

            std::mt19937 gen(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
            std::uniform_int_distribution<> dis(minVal, maxVal);

            for (int i = 0; i < n; ++i) {
                seq->Append(dis(gen));
            }

            std::cout << "Random data generated.\n";
        }

        std::cout
                << "Do you want to show sort?\n";
        std::cout << "1. Yes\n";
        std::cout << "2. No\n";
        int displayChoice = getValidatedIntInRange("Choice: ", 1, 2);

        if (displayChoice == 1) {
            std::cout << "Original data:\n";
            int elementsToShow = std::min(seq->GetLength(), MAX_PRINT);
            for (int i = 0; i < elementsToShow; ++i) {
                std::cout << seq->Get(i) << " ";
            }
            if (seq->GetLength() > MAX_PRINT) {
                std::cout << "... [Total elements: " << seq->GetLength() << "]";
            }
            std::cout << "\n";
        }

        auto start = std::chrono::high_resolution_clock::now();
        try {
            sorter->sort(*seq, compareInt);
        } catch (const std::exception &e) {
            std::cout << "An error occurred during sorting: " << e.what() << "\n";
            continue;
        } catch (...) {
            std::cout << "An unknown error occurred during sorting.\n";
            continue;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        if (displayChoice == 1) {
            std::cout << "Sorted data:\n";
            int elementsToShow = std::min(seq->GetLength(), MAX_PRINT);
            for (int i = 0; i < elementsToShow; ++i) {
                std::cout << seq->Get(i) << " ";
            }
            if (seq->GetLength() > MAX_PRINT) {
                std::cout << "... [Total elements: " << seq->GetLength() << "]";
            }
            std::cout << "\n";
        }

        std::cout << "Sorting took " << duration.count() << " seconds.\n";
        std::cout << "====================================\n";

    } while (true);

    std::cout << "Exiting...\n";
}