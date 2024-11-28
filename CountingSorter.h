#ifndef COUNTINGSORTER_H
#define COUNTINGSORTER_H

#include "ISorter.h"

template <typename T>
class CountingSorter : public ISorter<T> {
public:
    Sequence<T>* sort(Sequence<T>* seq, int (*Compare)(T, T)) override {
        countingSort(seq, Compare);
        return seq;
    }

private:
    void countingSort(Sequence<T>* seq, int (*Compare)(T, T)) {
        int n = seq->GetLength();

        T minElement = seq->Get(0);
        T maxElement = seq->Get(0);

        for (int i = 1; i < n; ++i) {
            if (Compare(seq->Get(i), minElement) < 0) {
                minElement = seq->Get(i);
            }
            if (Compare(seq->Get(i), maxElement) > 0) {
                maxElement = seq->Get(i);
            }
        }

        int range = maxElement - minElement + 1;

        int* count = new int[range]();

        for (int i = 0; i < n; ++i) {
            count[seq->Get(i) - minElement]++;
        }

        int index = 0;
        for (int i = 0; i < range; ++i) {
            while (count[i] > 0) {
                seq->Set(index, minElement + i);
                index++;
                count[i]--;
            }
        }

        delete[] count;
    }
};

#endif // COUNTINGSORTER_H
