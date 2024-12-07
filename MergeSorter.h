#ifndef MERGESORTER_H
#define MERGESORTER_H

#include "ISorter.h"

template <typename T>
class MergeSorter : public ISorter<T> {
public:
    Sequence<T>* sort(Sequence<T>& seq, int (*Compare)(T, T)) override {
        mergeSort(seq, 0, seq.GetLength() - 1, Compare);
        Sequence<T>* returnSequence = &seq;
        return returnSequence;
    }

private:
    void mergeSort(Sequence<T>& seq, int left, int right, int (*Compare)(T, T)) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            mergeSort(seq, left, mid, Compare);
            mergeSort(seq, mid + 1, right, Compare);

            merge(seq, left, mid, right, Compare);
        }
    }

    void merge(Sequence<T>& seq, int left, int mid, int right, int (*Compare)(T, T)) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        Sequence<T>* LeftSeq = seq.GetSubsequence(left, mid);
        Sequence<T>* RightSeq = seq.GetSubsequence(mid + 1, right);

        int i = 0;
        int j = 0;
        int k = left;

        while (i < n1 && j < n2) {
            if (Compare(LeftSeq->Get(i), RightSeq->Get(j)) <= 0) {
                seq.Set(k, LeftSeq->Get(i));
                i++;
            } else {
                seq.Set(k, RightSeq->Get(j));
                j++;
            }
            k++;
        }

        while (i < n1) {
            seq.Set(k, LeftSeq->Get(i));
            i++;
            k++;
        }

        while (j < n2) {
            seq.Set(k, RightSeq->Get(j));
            j++;
            k++;
        }

        delete LeftSeq;
        delete RightSeq;
    }
};

#endif // MERGESORTER_H
