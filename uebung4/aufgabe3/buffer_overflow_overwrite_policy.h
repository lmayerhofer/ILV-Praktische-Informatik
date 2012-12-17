#ifndef BUFFEROVERFLOWOVERWRITEPOLICY_H
#define BUFFEROVERFLOWOVERWRITEPOLICY_H

template <class T> class BufferOverflowOverwritePolicy {
	protected:
		void overflow(unsigned& start, unsigned& end, unsigned& max_size, T*& buffer, T new_element) {
			if(end == max_size) {
				end = 0;
				if(end == start) start++;		// update start if end and start are the same index
			} else {
				end++;
				if(end == start) start++;		// update start if end and start are the same index
			}

			buffer[end] = new_element;
		}
};

#endif