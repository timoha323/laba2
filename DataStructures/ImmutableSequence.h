#ifndef IMMUTABLESEQUENCE_H
#define IMMUTABLESEQUENCE_H



template<class T>
class ImmutableSequence {
public:
    virtual ImmutableSequence<T> *Append(const T &item) const = 0;

    virtual ImmutableSequence<T> *Prepend(const T &item) const = 0;

    virtual ImmutableSequence<T> *InsertAt(const T &item, int index) const = 0;

    virtual ImmutableSequence<T> *GetSubsequence(int startIndex, int endIndex) const = 0;

    virtual T GetFirst() const = 0;

    virtual T GetLast() const = 0;

    virtual T Get(int index) const = 0;

    virtual int GetLength() const = 0;

    virtual ~ImmutableSequence() {}
};

#endif // IMMUTABLESEQUENCE_H
