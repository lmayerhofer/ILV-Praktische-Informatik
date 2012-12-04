#ifndef SKIPNODE_H
#define SKIPNODE_H

template <class T> struct SkipNode {
    T value;
    SkipNode<T> **forward; // array of pointers

    SkipNode(int level, const T &value) {
        forward = new SkipNode<T> * [level + 1];
        memset(forward, 0, sizeof(SkipNode<T>*)*(level + 1));
        this->value = value;
    }

    ~SkipNode() { delete [] forward; }   
};

#endif