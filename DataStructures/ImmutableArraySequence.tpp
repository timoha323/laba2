#ifndef IMMUTABLEARRAYSEQUENCE_TPP
#define IMMUTABLEARRAYSEQUENCE_TPP

#include "ImmutableArraySequence.h"

template<class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const T* items, int count) {
    if (count < 0) throw std::invalid_argument(NEGETIVE_COUNT);
    this->items = new T[count];
    for (int i = 0; i < count; ++i) {
        this->items[i] = items[i];
    }
    this->count = count;
}

template<class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const ImmutableArraySequence<T>& sequence) {
    this->count = sequence.count;
    this->items = new T[count];
    for (int i = 0; i < count; ++i) {
        this->items[i] = sequence.items[i];
    }
}

template<class T>
ImmutableArraySequence<T>::~ImmutableArraySequence() {
    delete[] items;
}

template<class T>
ImmutableSequence<T>* ImmutableArraySequence<T>::Append(const T& item) const {
    T* newItems = new T[count + 1];
    for (int i = 0; i < count; ++i) {
        newItems[i] = items[i];
    }
    newItems[count] = item;
    return new ImmutableArraySequence<T>(newItems, count + 1);
}

template<class T>
ImmutableSequence<T>* ImmutableArraySequence<T>::Prepend(const T& item) const {
    T* newItems = new T[count + 1];
    newItems[0] = item;
    for (int i = 0; i < count; ++i) {
        newItems[i + 1] = items[i];
    }
    return new ImmutableArraySequence<T>(newItems, count + 1);
}

template<class T>
ImmutableSequence<T>* ImmutableArraySequence<T>::InsertAt(const T& item, int index) const {
    if (index < 0 || index > count) throw std::out_of_range(INDEX_OUT_OF_RANGE);
    T* newItems = new T[count + 1];
    for (int i = 0; i < index; ++i) {
        newItems[i] = items[i];
    }
    newItems[index] = item;
    for (int i = index + 1; i <= count; ++i) {
        newItems[i] = items[i - 1];
    }
    return new ImmutableArraySequence<T>(newItems, count + 1);
}

template<class T>
ImmutableSequence<T>* ImmutableArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= count || startIndex > endIndex)
        throw std::out_of_range("Index out of range");
    int subLength = endIndex - startIndex + 1;
    T* subItems = new T[subLength];
    for (int i = 0; i < subLength; ++i) {
        subItems[i] = items[startIndex + i];
    }
    return new ImmutableArraySequence<T>(subItems, subLength);
}

template<class T>
T ImmutableArraySequence<T>::GetFirst() const {
    if (count == 0) throw std::out_of_range(EMPTYIMARRAYSEQ);
    return items[0];
}

template<class T>
T ImmutableArraySequence<T>::GetLast() const {
    if (count == 0) throw std::out_of_range(EMPTYIMARRAYSEQ);
    return items[count - 1];
}

template<class T>
T ImmutableArraySequence<T>::Get(int index) const {
    if (index < 0 || index >= count) throw std::out_of_range(INDEX_OUT_OF_RANGE);
    return items[index];
}

template<class T>
int ImmutableArraySequence<T>::GetLength() const {
    return count;
}

#endif // IMMUTABLEARRAYSEQUENCE_TPP
