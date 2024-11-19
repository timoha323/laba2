#ifndef IMMUTABLEARRAYSEQUENCE_H
#define IMMUTABLEARRAYSEQUENCE_H

#include "ImmutableSequence.h"
#include <stdexcept>

#define NEGETIVE_COUNT "Count cannot be negative"
#define INDEX_OUT_OF_RANGE "Index out of range"
#define EMPTYIMARRAYSEQ "Array is empty"

template<class T>
class ImmutableArraySequence : public ImmutableSequence<T> {
private:
    T* items;
    int count;

public:
    ImmutableArraySequence(const T* items, int count);
    ImmutableArraySequence(const ImmutableArraySequence<T>& sequence);
    ~ImmutableArraySequence();

    ImmutableSequence<T>* Append(const T& item) const override;
    ImmutableSequence<T>* Prepend(const T& item) const override;
    ImmutableSequence<T>* InsertAt(const T& item, int index) const override;
    ImmutableSequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    int GetLength() const override;
};

#include "ImmutableArraySequence.tpp"

#endif // IMMUTABLEARRAYSEQUENCE_H
