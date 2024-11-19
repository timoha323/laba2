#ifndef LISTSEQUENCE_TPP
#define LISTSEQUENCE_TPP

#include "ListSequence.h"

template<class T>
ListSequence<T>::ListSequence() : list() {}

template<class T>
ListSequence<T>::ListSequence(const T* items, int count) : list(items, count) {}

template<class T>
ListSequence<T>::ListSequence(const ListSequence<T>& sequence) : list(sequence.list) {}

template<class T>
ListSequence<T>::ListSequence(const LinkedList<T>& list) : list(list) {}

template<class T>
T ListSequence<T>::GetFirst() const {
    if (list.GetLength() == 0) throw std::out_of_range(EMPTYLISTSEQUECE);
    return list.GetFirst();
}

template<class T>
T ListSequence<T>::GetLast() const {
    if (list.GetLength() == 0) throw std::out_of_range(EMPTYLISTSEQUECE);
    return list.GetLast();
}

template<class T>
T ListSequence<T>::Get(int index) const {
    if (index < 0 || index >= list.GetLength()) throw std::out_of_range(INDEX_OUT_OF_RANGE);
    return list.Get(index);
}

template<class T>
Sequence<T>* ListSequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= list.GetLength() || startIndex > endIndex)
        throw std::out_of_range(INDEX_OUT_OF_RANGE);

    ListSequence<T>* subList = new ListSequence<T>();
    for (int i = startIndex; i <= endIndex; ++i) {
        subList->Append(list.Get(i));
    }
    return subList;
}

template<class T>
int ListSequence<T>::GetLength() const {
    return list.GetLength();
}

template<class T>
void ListSequence<T>::Append(const T& item) {
    list.Append(item);
}

template<class T>
void ListSequence<T>::Prepend(const T& item) {
    list.Prepend(item);
}

template<class T>
void ListSequence<T>::InsertAt(const T& item, int index) {
    list.InsertAt(item, index);
}

template<class T>
void ListSequence<T>::Set(int index, const T& item) {
    if (index < 0 || index >= list.GetLength()) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    list.Set(index, item);
}

template<class T>
Sequence<T>* ListSequence<T>::Concat(Sequence<T>* otherList) const {
    ListSequence<T>* result = new ListSequence<T>();
    for (int i = 0; i < this->GetLength(); i++) {
        result->Append(this->Get(i));
    }
    for (int i = 0; i < otherList->GetLength(); i++) {
        result->Append(otherList->Get(i));
    }
    return result;
}

#endif // LISTSEQUENCE_TPP
