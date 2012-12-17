#ifndef BUFFEROVERFLOWIGNOREPOLICY_H
#define BUFFEROVERFLOWIGNOREPOLICY_H

template <class T> class BufferOverflowIgnorePolicy {
	protected:
		void overflow(unsigned& start, unsigned& end, unsigned& max_size, T*& buffer, T new_element) { }
};

#endif