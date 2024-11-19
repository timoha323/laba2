#ifndef LISTSEQUENCE_H
#define LISTSEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"

#define EMPTYLISTSEQUECE "Sequence is empty"

template<class T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T> list;

public:
    ListSequence();
    ListSequence(const T* items, int count);
    ListSequence(const ListSequence<T>& sequence);
    ListSequence(const LinkedList<T>& list);

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

#include "ListSequence.tpp"

#endif // LISTSEQUENCE_H
