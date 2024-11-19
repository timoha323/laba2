#ifndef ISORTER_H
#define ISORTER_H

#include "DataStructures/Sequence.h"

template <typename T>
class ISorter {
public:
    virtual Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(T, T)) = 0;
    virtual ~ISorter() {}
};

#endif // ISORTER_H
