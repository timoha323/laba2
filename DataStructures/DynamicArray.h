#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdexcept>

#define INDEX_OUT_OF_RANGE "Index out of range"
#define NEGATIVE_SIZE "New size must be greater than or equal to zero."

template<class T>
class DynamicArray {
private:
    T* data;
    size_t length;

public:
    DynamicArray();
    DynamicArray(T* items, int count);
    DynamicArray(int size);
    DynamicArray(const DynamicArray<T>& dynamicArray);
    ~DynamicArray();

    T Get(int index) const;
    void Set(int index, T value);
    int GetSize() const;
    void Resize(int newSize);

    T& operator[](int index);
    const T& operator[](int index) const;
};

#include "DynamicArray.tpp"

#endif // DYNAMICARRAY_H

