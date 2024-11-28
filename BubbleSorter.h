#ifndef BUBBLESORTER_H
#define BUBBLESORTER_H

#include "ISorter.h"

template <typename T>
class BubbleSorter : public ISorter<T> {
public:
    Sequence<T>* sort(Sequence<T>* seq, int (*Compare)(T, T)) override {
        bubbleSort(seq, Compare);
        return seq;
    }

private:
    void bubbleSort(Sequence<T>* seq, int (*Compare)(T, T)) {
        int n = seq->GetLength();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (Compare(seq->Get(j), seq->Get(j + 1)) > 0) {
                    T temp = seq->Get(j);
                    seq->Set(j, seq->Get(j + 1));
                    seq->Set(j + 1, temp);
                }
            }
        }
    }
};

#endif // BUBBLESORTER_H
