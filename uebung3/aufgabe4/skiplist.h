#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>

#include "skipnode.h"
#include "skiplist.h"
#include "student.h"

using namespace std;

const int MAX_LEVEL = 5;
const float P = 0.5;

template <class T> struct SkipList {
	SkipNode<T> *header;
    int level;

    SkipList() {
        header = new SkipNode<T>(MAX_LEVEL, T());
        level = 0;
    }

    ~SkipList() {
        delete header;
    }

    void print() const;
    bool search(const T &) const;
    void insert(const T &);
};

/*****************************************************************************/

float frand() {
    return (float) rand() / RAND_MAX;
}

int random_level() {
    static bool first = true;

    if (first) {
        srand( (unsigned)time( NULL ) );
        first = false;
    }

    int lvl = (int)(log(frand())/log(1.-P));
    return lvl < MAX_LEVEL ? lvl : MAX_LEVEL;
}

template <class T> void SkipList<T>::print() const {
    const SkipNode<T> *x = header->forward[0];
    cout << "{";
    while (x != NULL) {
        cout << x->value;
        x = x->forward[0];
        if (x != NULL)
            cout << "\n";
    }    
    cout << "}\n";
}

template <class T> bool SkipList<T>::search(const T &search_value) const {
    const SkipNode<T> *x = header;
    for (int i = level; i >= 0; i--) {
        while (x->forward[i] != NULL && x->forward[i]->value < search_value) {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    return x != NULL && x->value == search_value;
}

template <class T> void SkipList<T>::insert(const T &value) {
    SkipNode<T> *x = header;	
    SkipNode<T> *update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(SkipNode<T>*)*(MAX_LEVEL + 1));

    for (int i = level; i >= 0; i--) {
        while (x->forward[i] != NULL && x->forward[i]->value < value) {
            x = x->forward[i];
        }
        update[i] = x; 
    }
    x = x->forward[0];

    if (x == NULL || x->value != value) {        
        int lvl = random_level();
  
        if (lvl > level) {
    	    for (int i = level + 1; i <= lvl; i++) {
    	        update[i] = header;
    	    }
    	    level = lvl;
	    }

        x = new SkipNode<T>(lvl, value);
    	for (int i = 0; i <= lvl; i++) {
    	    x->forward[i] = update[i]->forward[i];
    	    update[i]->forward[i] = x;
    	}
    }
}

#endif