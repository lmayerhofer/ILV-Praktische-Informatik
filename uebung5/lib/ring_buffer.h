#ifndef RING_BUFFER
#define RING_BUFFER

#include <string>

using namespace std;

class RingBuffer {

public:
	RingBuffer() {
		data = new unsigned[0];
		size = 0;
	}
	
	RingBuffer(unsigned s) : size(s) {
		data = new unsigned[s];
		index = 0;
	}

	// Copy constructor
	RingBuffer(RingBuffer &other) {
		size = other.size;
		index = other.index;
		data = new unsigned[size];
		for(unsigned i=0; i<size; i++) {
			data[i] = other.data[i];
		}
	}

	~RingBuffer() {
		delete[] data;
	}
	
	void set_size(unsigned size) {
		delete[] data;
		data = new unsigned[size];
		this->size = size;
	}

	int find(unsigned tag) {
		for(unsigned i=0; i<size; i++) {
			if (data[i]==tag)
				return i;
		}
		return -1;
	}
	
	unsigned push(unsigned tag) {
		// cout << "index: " << index << " mod: " << (index % size) << " data: " << data[index % size] << " tag: " << tag << "\n";
		
		data[index % size] = tag;
		index++;

		return ((index-1) % size);
	}
	
	unsigned get_size() {
		return size;
	}
	
	void print() const {
		cout << "[ ";
		for(unsigned i=0; i<size; i++) {
			cout << data[i] << " ";
		}
		cout << " ]\n";
	}

	RingBuffer& operator=(RingBuffer &other) {
		size = other.size;
		index = other.index;
		data = new unsigned[size];
		for(unsigned i=0; i<size; i++) {
			data[i] = other.data[i];
		}
		return *this;
	}

private:
	unsigned size;
	unsigned *data;
	
	unsigned index;
};

#endif
