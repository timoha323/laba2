#ifndef LINKEDLIST_TPP
#define LINKEDLIST_TPP

#include "LinkedList.h"
#include <stdexcept>
#include <cstddef>

template<class T>
LinkedListNode<T>::LinkedListNode(const T& value, LinkedListNode<T>* next) : value(value), next(next) {}

template<class T>
void LinkedList<T>::Clear() {
    while (head != nullptr) {
        LinkedListNode<T>* current = head;
        head = head->next;
        delete current;
    }
    tail = nullptr;
    length = 0;
}

template<class T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), length(0) {}

template<class T>
LinkedList<T>::LinkedList(const T* items, int count) : head(nullptr), tail(nullptr), length(0) {
    for (int i = 0; i < count; ++i) {
        Append(items[i]);
    }
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), length(0) {
    LinkedListNode<T>* current = list.head;
    while (current != nullptr) {
        Append(current->value);
        current = current->next;
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    Clear();
}

template<class T>
LinkedList<T>* LinkedList<T>::GetSubList(int startIndex, int endIndex) {
    if (startIndex < 0 || endIndex < 0 || startIndex > endIndex || endIndex >= this->length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    auto* subList = new LinkedList<T>();
    LinkedListNode<T>* current = this->head;
    for (int i = 0; i < startIndex; ++i) {
        current = current->next;
    }
    for (int i = startIndex; i <= endIndex; ++i) {
        subList->Append(current->value);
        current = current->next;
    }
    return subList;
}

template<class T>
void LinkedList<T>::Append(T item) {
    LinkedListNode<T>* node = new LinkedListNode<T>(item, nullptr);
    if (tail == nullptr) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
    length++;
}

template<class T>
size_t LinkedList<T>::GetLength() const {
    return length;
}

template<class T>
T LinkedList<T>::GetFirst() const {
    if (head == nullptr) throw std::out_of_range(EMPTYLINKEDLIST);
    return head->value;
}

template<class T>
T LinkedList<T>::GetLast() const {
    if (tail == nullptr) throw std::out_of_range(EMPTYLINKEDLIST);
    return tail->value;
}

template<class T>
T LinkedList<T>::Get(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    LinkedListNode<T>* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->value;
}

template<class T>
void LinkedList<T>::Prepend(T item) {
    LinkedListNode<T>* newNode = new LinkedListNode<T>(item, head);
    head = newNode;
    if (length == 0) {
        tail = newNode;
    }
    length++;
}

template<class T>
void LinkedList<T>::InsertAt(T item, int index) {
    if (index < 0 || index > length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    if (index == 0) {
        Prepend(item);
        return;
    }
    if (index == length) {
        Append(item);
        return;
    }
    LinkedListNode<T>* current = head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    LinkedListNode<T>* newNode = new LinkedListNode<T>(item, current->next);
    current->next = newNode;
    length++;
}

template<class T>
void LinkedList<T>::Set(int index, const T& value) {
    if (index < 0 || index >= length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    LinkedListNode<T>* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    current->value = value;
}


#endif // LINKEDLIST_TPP
