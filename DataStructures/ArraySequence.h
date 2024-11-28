
#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"

#define INDEX_OUT_OF_RANGE "Index out of range"
#define EMPTYARRAYSEQ "Array is empty"

template<class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* data;
    int length;
    int capacity;

    void ensureCapacity(int minCapacity);

public:
    ArraySequence();
    ArraySequence(const T* items, int count);
    ArraySequence(const ArraySequence<T>& arraySequence);
    ~ArraySequence();

    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    int GetLength() const override;
    void Append(const T& item) override;
    void Prepend(const T& item) override;
    void InsertAt(const T& item, int index) override;
    void Set(int index, const T& item) override;
    Sequence<T>* Concat(Sequence<T>* list) const override;
};

#include "ArraySequence.tpp"

#endif // ARRAYSEQUENCE_H
