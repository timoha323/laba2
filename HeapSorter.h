#ifndef HEAPSORTER_H
#define HEAPSORTER_H

#include "ISorter.h"

template <typename T>
class HeapSorter : public ISorter<T> {
public:
    Sequence<T>* sort(Sequence<T>& seq, int (*Compare)(T, T)) override {
        int n = seq.GetLength();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(seq, n, i, Compare);

        for (int i = n - 1; i >= 0; i--) {

            T temp = seq.Get(0);
            seq.Set(0, seq.Get(i));
            seq.Set(i, temp);

            heapify(seq, i, 0, Compare);
        }
        Sequence<T>* returnSequence = &seq;
        return returnSequence;
    }

private:
    void heapify(Sequence<T>& seq, int n, int i, int (*Compare)(T, T)) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && Compare(seq.Get(left), seq.Get(largest)) > 0)
            largest = left;

        if (right < n && Compare(seq.Get(right), seq.Get(largest)) > 0)
            largest = right;

        if (largest != i) {
            T swap = seq.Get(i);
            seq.Set(i, seq.Get(largest));
            seq.Set(largest, swap);

            heapify(seq, n, largest, Compare);
        }
    }
};

#endif // HEAPSORTER_H
