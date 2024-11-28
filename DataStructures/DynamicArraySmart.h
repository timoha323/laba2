#ifndef DYNAMICARRAYSMART_H
#define DYNAMICARRAYSMART_H

#include "Sequence.h"
#include "../smart_pointers/uniquePointer.h"
#include <stdexcept>

#define EMPTY_DYNAMIC_ARRAY "DynamicArraySmart is empty"
#define OUT_OF_RANGE "Index out of range"
#define SUBSEQ_ERR "Invalid subsequence indices"

template <typename T>
class DynamicArraySmart : public Sequence<T> {
private:
    UniquePtr<T[]> data;
    int capacity;
    int length;

    void resize(int newCapacity) {
        UniquePtr<T[]> newData(new T[newCapacity]);
        for (int i = 0; i < length; ++i) {
            newData[i] = std::move(data[i]);
        }
        data = std::move(newData);
        capacity = newCapacity;
    }

public:
    DynamicArraySmart() : data(nullptr), capacity(0), length(0) {}

    DynamicArraySmart(const T* inputData, int size) : data(nullptr), capacity(size), length(size) {
        if (size > 0) {
            data.reset(new T[size]);
            for (int i = 0; i < size; ++i) {
                this->data[i] = inputData[i];
            }
        }
    }

    ~DynamicArraySmart() override = default;

    T GetFirst() const override {
        if (length == 0)
            throw std::out_of_range(EMPTY_DYNAMIC_ARRAY);
        return data[0];
    }

    T GetLast() const override {
        if (length == 0)
            throw std::out_of_range(EMPTY_DYNAMIC_ARRAY);
        return data[length - 1];
    }

    T Get(int index) const override {
        if (index < 0 || index >= length)
            throw std::out_of_range(OUT_OF_RANGE);
        return data[index];
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex >= length || startIndex > endIndex)
            throw std::out_of_range(SUBSEQ_ERR);

        auto* subseq = new DynamicArraySmart<T>();
        for (int i = startIndex; i <= endIndex; ++i) {
            subseq->Append(data[i]);
        }
        return subseq;
    }

    int GetLength() const override {
        return length;
    }

    void Append(const T& item) override {
        if (length == capacity) {
            int newCapacity = capacity == 0 ? 1 : capacity * 2;
            resize(newCapacity);
        }
        data[length++] = item;
    }

    void Prepend(const T& item) override {
        if (length == capacity) {
            int newCapacity = capacity == 0 ? 1 : capacity * 2;
            resize(newCapacity);
        }
        for (int i = length; i > 0; --i) {
            data[i] = std::move(data[i - 1]);
        }
        data[0] = item;
        ++length;
    }

    void InsertAt(const T& item, int index) override {
        if (index < 0 || index > length)
            throw std::out_of_range(OUT_OF_RANGE);
        if (length == capacity) {
            int newCapacity = capacity == 0 ? 1 : capacity * 2;
            resize(newCapacity);
        }
        for (int i = length; i > index; --i) {
            data[i] = std::move(data[i - 1]);
        }
        data[index] = item;
        ++length;
    }

    Sequence<T>* Concat(Sequence<T>* list) const override {
        auto* newArray = new DynamicArraySmart<T>();
        for (int i = 0; i < length; ++i) {
            newArray->Append(data[i]);
        }
        for (int i = 0; i < list->GetLength(); ++i) {
            newArray->Append(list->Get(i));
        }
        return newArray;
    }

    void Set(int index, const T& item) override {
        if (index < 0 || index >= length)
            throw std::out_of_range(OUT_OF_RANGE);
        data[index] = item;
    }
};

#endif // DYNAMICARRAYSMART_H
