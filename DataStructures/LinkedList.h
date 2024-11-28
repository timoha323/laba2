#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstddef>
#include <stdexcept>

#define INDEX_OUT_OF_RANGE "Index out of range"
#define EMPTYLINKEDLIST "LinkedList is empty"

template<class T>
class LinkedListNode {
public:
    T value;
    LinkedListNode<T>* next;

    LinkedListNode(const T& value, LinkedListNode<T>* next = nullptr);
};

template<class T>
class LinkedList {
private:
    LinkedListNode<T>* head;
    LinkedListNode<T>* tail;
    size_t length;

public:
    LinkedList();
    LinkedList(const T* items, int count);
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();

    LinkedList<T>* GetSubList(int startIndex, int endIndex);
    void Append(T item);
    void Prepend(T item);
    void InsertAt(T item, int index);
    size_t GetLength() const;
    T GetFirst() const;
    T GetLast() const;
    T Get(int index) const;
    void Set(int index, const T& value);
    void Clear();

    T& operator[](int index) {
        if (index < 0 || index >= length) {
            throw std::out_of_range(INDEX_OUT_OF_RANGE);
        }
        LinkedListNode<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    class Iterator {
    private:
        LinkedListNode<T>* current;

    public:
        Iterator(LinkedListNode<T>* start) : current(start) {}

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        T& operator*() const {
            return current->value;
        }

        T* operator->() const {
            return &(current->value);
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
    Iterator begin() const{
        return Iterator(head);
    }

    Iterator end() const{
        return Iterator(nullptr);
    }
};

#include "LinkedList.tpp"

#endif // LINKEDLIST_H