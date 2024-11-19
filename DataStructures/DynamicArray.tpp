#ifndef DYNAMICARRAY_TPP
#define DYNAMICARRAY_TPP

#include "DynamicArray.h"

template<class T>
T& DynamicArray<T>::operator[](int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    return data[index];
}

template<class T>
const T& DynamicArray<T>::operator[](int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    return data[index];
}

template<class T>
DynamicArray<T>::DynamicArray() : data(nullptr), length(0) {}

template<class T>
DynamicArray<T>::DynamicArray(T* items, int count) : length(count) {
    data = new T[length];
    for (int i = 0; i < count; ++i) {
        data[i] = items[i];
    }
}

template<class T>
DynamicArray<T>::DynamicArray(int size) : length(size) {
    data = new T[length];
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArray)
        : length(dynamicArray.length) {
    data = new T[length];
    for (size_t i = 0; i < length; ++i) {
        data[i] = dynamicArray.data[i];
    }
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<class T>
T DynamicArray<T>::Get(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    return data[index];
}

template<class T>
void DynamicArray<T>::Set(int index, T value) {
    if (index < 0 || index >= length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    data[index] = value;
}

template<class T>
int DynamicArray<T>::GetSize() const {
    return length;
}

template<class T>
void DynamicArray<T>::Resize(int newSize) {
    if (newSize < 0) {
        throw std::length_error(NEGATIVE_SIZE);
    }

    T* newData = (newSize > 0) ? new T[newSize] : nullptr;
    int elementsToCopy = (newSize > length) ? length : newSize;


    for (int i = 0; i < elementsToCopy; ++i) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    length = newSize;

}


#endif // DYNAMICARRAY_TPP


