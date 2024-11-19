#pragma once
#include <cstddef>
template <typename T>
class UniquePtr {
private:
    T* ptr;

public:

    UniquePtr() : ptr(nullptr) {}

    explicit UniquePtr(T* p) : ptr(p) {}

    UniquePtr(const UniquePtr<T>&) = delete;

    UniquePtr& operator=(const UniquePtr<T>&) = delete;

    UniquePtr(UniquePtr<T>&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr<T>&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    ~UniquePtr() {
        delete ptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }

    T *release() {
        T *temp = ptr;
        ptr = nullptr;
        return temp;
    }

    T* get() const {
        return ptr;
    }

    bool isNull() const {
        return ptr == nullptr;
    }
};


template<typename T>
class UniquePtr<T[]> {
private:
    T *ptr;

public:
    explicit UniquePtr(T *p = nullptr) : ptr(p) {}
    ~UniquePtr() {
        delete[] ptr;
    }

    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;

    UniquePtr(UniquePtr &&other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UniquePtr &operator=(UniquePtr &&other) noexcept {
        if (this != &other) {
            delete[] ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T &operator*() const { return *ptr; }
    T *operator->() const { return ptr; }
    T &operator[]() const { return (*ptr)[]; }

    void reset(T *p = nullptr) {
        delete[] ptr;
        ptr = p;
    }

    T *release() {
        T *temp = ptr;
        ptr = nullptr;
        return temp;
    }

    T* get() const { return ptr; }

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