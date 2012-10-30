/*
 * Aufgabe 1_1 - heap.cpp
 * Lukas Mayerhofer
 * 27.10.12
 */

#include <iostream>
//#include <iomanip>
//#include <math.h>
#include <assert.h>
#include "heap.h"
#include "student.h"

// Add new element to heap
template<class T> void Heap<T>::push(T d) {
	assert(elements < size);
	
	data[elements++] = d;
	unsigned idx = elements-1;

	while (idx != 0) {
		unsigned pidx = parent_index(idx);
		if (data[pidx] < d)
			std::swap(data[idx], data[pidx]);
		else break;
		idx = pidx;
	}
}

// Remove element from heap
template<class T> void Heap<T>::pop() {
	assert(elements > 0);
	
	data[0] = data[--elements];
	unsigned idx = 0;
	do {
		unsigned childs = children(idx);
		if (childs == 0) break;

		unsigned max_idx = left_index(idx);
		if (childs == 2) {
            if (data[max_idx] < data[max_idx + 1])
                max_idx++;
		}
		
		if (data[idx] < data[max_idx]) {
			std::swap(data[idx], data[max_idx]);
			idx = max_idx;
		}
		else break;
	} while (true);
}

// Print elements
template<class T> void Heap<T>::print() const {
	std::cout << "\n[";
	for (int i = 0; i < elements; i++) {
		//std::cout << i + 1 << ". Element: " << data[i] << std::endl;
		if(i == elements - 1)
			std::cout << data[i];
		else
			std::cout << data[i] << ", ";
	}
	std::cout << "]\n";
}

// Sort elements with Heap Sort
template<class T> void Heap<T>::sort() {
	std::cout << "[";
	while(elements > 0) {
		if(elements == 1)
			std::cout << data[0];
		else
			std::cout << data[0] << ", ";
		pop();
	}
	std::cout << "]";
}