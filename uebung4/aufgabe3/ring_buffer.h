#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <iostream>

#include "buffer_overflow_exception_policy.h"
#include "buffer_overflow_ignore_policy.h"
#include "buffer_overflow_overwrite_policy.h"

#include "empty_buffer_exception_policy.h"
#include "empty_buffer_default_policy.h"

template <
    class T,
    template <class> class BufferOverflowPolicy = BufferOverflowIgnorePolicy,
    template <class> class EmptyBufferPolicy = EmptyBufferDefaultPolicy
> class RingBuffer : public BufferOverflowPolicy<T>, public EmptyBufferPolicy<T> {
    public:
        RingBuffer() {
            max_size = 10;
            buffer = new T[max_size];     // create new buffer with standard size (=10)
            start = end = num_elements = 0;
        }
        RingBuffer( unsigned m ) {
            max_size = m;
            if(max_size > 0) buffer = new T[max_size];
            start = end = num_elements = 0;
        }
        ~RingBuffer() {
            if(buffer != NULL) {
                delete [] buffer;
            }
        }

        void print() const {
            std::cout << "\nall: ";
            for(int i = 0; i < max_size; i++) {
                if(i == 0) {
                    std::cout << "[ "<< buffer[i] << ", ";
                } else if(i == max_size - 1) {
                    std::cout << buffer[i] << " ]" << std::endl;
                } else {
                    std::cout << buffer[i] << ", ";
                }
            }
        }

        T read() {
            T element;

            if(num_elements <= 0) {
                element = this->empty();
            } else {
                if(start == max_size) start = 0;
                element = buffer[start];
                update(start);
                num_elements--;
            }

            std::cout << "read: " << element << std::endl;

            return element;
        }

        void write(T new_element) {
            if(num_elements >= max_size) {
                this->overflow(start, end, max_size, buffer, new_element);
            } else {
                buffer[end] = new_element;
                update(end);                        // update index of buffer-end
                num_elements++;
            }
        }

        void update(unsigned& currentIndex) {
            if(currentIndex == max_size) {
                currentIndex = 0;
            } else {
                currentIndex++;
            }
        }

    private:
        unsigned max_size;
        unsigned start;                  // index of oldest element
        unsigned end;                    // index of current element
        unsigned num_elements;           // number of elements currently in array
        T *buffer;
};

#endif

/*** TESTS ***/

// 1. Was wenn Buffer leer?
// 2. Was wenn Buffer voll?
// 3. Wenn Buffer voll => Wird Startposition angepasst?
// 4. Wenn Buffer voll => Werden die ersten Werte überschrieben?
// 5. Funktionieren verschiedene Datentypen?
