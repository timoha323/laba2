#ifndef ARRAYSEQUENCE_TPP
#define ARRAYSEQUENCE_TPP

#include "ArraySequence.h"
#include <stdexcept>

template<class T>
ArraySequence<T>::ArraySequence() : data(new DynamicArray<T>(10)), length(0), capacity(10) {}

template<class T>
ArraySequence<T>::ArraySequence(const T* items, int count) : data(new DynamicArray<T>(count)), length(count), capacity(count) {
    for (int i = 0; i < count; ++i) {
        data->Set(i, items[i]);
    }
}

template<class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& arraySequence)
        : data(new DynamicArray<T>(arraySequence.capacity)), length(arraySequence.length), capacity(arraySequence.capacity) {
    for (int i = 0; i < length; ++i) {
        data->Set(i, arraySequence.data->Get(i));
    }
}

template<class T>
ArraySequence<T>::~ArraySequence() {
    delete data;
}

template<class T>
T ArraySequence<T>::GetFirst() const {
    if (length == 0) {
        throw std::out_of_range(EMPTYARRAYSEQ);
    }
    return data->Get(0);
}

template<class T>
T ArraySequence<T>::GetLast() const {
    if (length == 0) {
        throw std::out_of_range(EMPTYARRAYSEQ);
    }
    return data->Get(length - 1);
}

template<class T>
T ArraySequence<T>::Get(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    return data->Get(index);
}

template<class T>
Sequence<T>* ArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= length || startIndex > endIndex) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    int subLength = endIndex - startIndex + 1;
    T* items = new T[subLength];
    for (int i = 0; i < subLength; ++i) {
        items[i] = data->Get(startIndex + i);
    }
    Sequence<T>* subsequence = new ArraySequence<T>(items, subLength);
    delete[] items;
    return subsequence;
}

template<class T>
int ArraySequence<T>::GetLength() const {
    return length;
}

template<class T>
void ArraySequence<T>::ensureCapacity(int minCapacity) {
    if (minCapacity > capacity) {
        int newCapacity = capacity * 2;
        if (newCapacity < minCapacity) {
            newCapacity = minCapacity;
        }
        data->Resize(newCapacity);
        capacity = newCapacity;
    }
}

template<class T>
void ArraySequence<T>::Append(const T& item) {
    ensureCapacity(length + 1);
    data->Set(length, item);
    length++;
}

template<class T>
void ArraySequence<T>::Prepend(const T& item) {
    ensureCapacity(length + 1);
    for (int i = length; i > 0; --i) {
        data->Set(i, data->Get(i - 1));
    }
    data->Set(0, item);
    length++;
}

template<class T>
void ArraySequence<T>::InsertAt(const T& item, int index) {
    if (index < 0 || index > length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    ensureCapacity(length + 1);
    for (int i = length; i > index; --i) {
        data->Set(i, data->Get(i - 1));
    }
    data->Set(index, item);
    length++;
}

template<class T>
void ArraySequence<T>::Set(int index, const T& item) {
    if (index < 0 || index >= length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    data->Set(index, item);
}

template<class T>
Sequence<T>* ArraySequence<T>::Concat(Sequence<T>* list) const {
    int newLength = length + list->GetLength();
    T* newArray = new T[newLength];
    for (int i = 0; i < length; ++i) {
        newArray[i] = data->Get(i);
    }
    for (int i = 0; i < list->GetLength(); ++i) {
        newArray[length + i] = list->Get(i);
    }
    Sequence<T>* newSequence = new ArraySequence<T>(newArray, newLength);
    delete[] newArray;
    return newSequence;
}

#endif // ARRAYSEQUENCE_TPP
