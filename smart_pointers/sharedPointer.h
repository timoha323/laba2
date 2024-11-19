#pragma once
#include <cstddef>
template<typename T>
class SharedPointer {
private:
    T* ptr;
    size_t *referenceCount;

    void clean(){
        if (referenceCount && --(*referenceCount) == 0) {
            delete ptr;
            delete referenceCount;
        }
    }

public:
    explicit SharedPointer(T *p = nullptr) : ptr(p), referenceCount(new size_t(1)) {}

    SharedPointer(const SharedPointer &other)
            : ptr(other.ptr), referenceCount(other.referenceCount) {
        if (referenceCount) {
            ++(*referenceCount);
        }
    }

    SharedPointer &operator=(const SharedPointer &other) {
        if (this != &other) {
            clean();
            ptr = other.ptr;
            referenceCount = other.referenceCount;
            if (referenceCount) {
                ++(*referenceCount);
            }
        }
        return *this;
    }
    ~SharedPointer() {
        clean();
    }

    T &operator*() const { return *ptr; }
    T *operator->() const { return ptr; }

    size_t use_count() const { return referenceCount ? *referenceCount : 0; }

    void reset(T *p = nullptr) {
        clean();
        ptr = p;
        referenceCount = new size_t(1);
    }

    T getRefCount() const {
        return referenceCount ? *referenceCount : 0;
    }

    bool null() const {
        return ptr == nullptr;
    }
};

template<typename T>
class SharedPointer<T[]> {
private:
    T* ptr;
    size_t *referenceCount;

    void clean(){
        if (referenceCount && --(*referenceCount) == 0) {
            delete[] ptr;
            delete referenceCount;
        }
    }

public:
    explicit SharedPointer(T *p = nullptr) : ptr(p), referenceCount(new size_t(1)) {}

    SharedPointer(const SharedPointer &other)
            : ptr(other.ptr), referenceCount(other.referenceCount) {
        if (referenceCount) {
            ++(*referenceCount);
        }
    }

    SharedPointer &operator=(const SharedPointer &other) {
        if (this != &other) {
            clean();
            ptr = other.ptr;
            referenceCount = other.referenceCount;
            if (referenceCount) {
                ++(*referenceCount);
            }
        }
        return *this;
    }
    ~SharedPointer() {
        clean();
    }

    T &operator*() const { return *ptr; }
    T *operator->() const { return ptr; }

    size_t use_count() const { return referenceCount ? *referenceCount : 0; }

    void reset(T *p = nullptr) {
        clean();
        ptr = p;
        referenceCount = new size_t(1);
    }

    bool null() const {
        return ptr == nullptr;
    }

    const T& operator[](size_t i) const{
        return ptr[i];
    }
    T& operator[](size_t i) {
        return ptr[i];
    }

};