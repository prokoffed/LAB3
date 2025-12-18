#ifndef TSTACK_H
#define TSTACK_H

#include <iostream>

template <class T>
class TStack {
private:
    T* pMem;
    int size;
    int top;

    void resize(int newSize) {
        T* tmp = new T[newSize];
        for (int i = 0; i <= top && i < newSize; i++) {
            tmp[i] = pMem[i];
        }
        delete[] pMem;
        pMem = tmp;
        size = newSize;
    }

public:
    TStack(int sz = 10) {
        if (sz <= 0) throw "Invalid stack size";
        size = sz;
        top = -1;
        pMem = new T[size];
    }

    TStack(const TStack& s) {
        size = s.size;
        top = s.top;
        pMem = new T[size];
        for (int i = 0; i <= top; i++) {
            pMem[i] = s.pMem[i];
        }
    }

    ~TStack() {
        delete[] pMem;
    }

    void push(T val) {
        if (isFull()) {
            resize(size * 2);
        }
        pMem[++top] = val;
    }

    T pop() {
        if (isEmpty()) throw "Stack is empty";
        return pMem[top--];
    }

    T peek() const {
        if (isEmpty()) throw "Stack is empty";
        return pMem[top];
    }

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == size - 1;
    }

    int getSize() const {
        return top + 1;
    }
};

#endif