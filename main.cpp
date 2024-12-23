#include "interface.h"
#include "FileSorting.h"

int main() {
    try {
        FileSorting fileSorting("peoples.txt");
        fileSorting.sort("HeapSort");
    } catch(...){}
    runInterface();
    return 0;
}