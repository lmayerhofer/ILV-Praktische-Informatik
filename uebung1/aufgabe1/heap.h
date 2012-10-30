/*
 * Aufgabe 1_1 - heap.h
 * Lukas Mayerhofer
 * 27.10.12
 */

template<class T> class Heap {
	public:
		Heap(unsigned n) : elements(0), size(n), data(new T[n]) { }
		virtual ~Heap() { delete [] data; }
		
		bool empty() const { return elements; }
		T top() const {
            assert(elements > 0);
			return data[0];
		}
		void push(T d);
		void pop();
		void print() const;

	private:
		unsigned elements;
		unsigned size;
		T* data;
		
		unsigned left_index(unsigned idx) const { return 2 * idx + 1; }
		unsigned right_index(unsigned idx) const { return 2 * idx + 2; }
		unsigned parent_index(unsigned idx) const { return (idx - 1) / 2; }
		unsigned children(unsigned idx) const {
			if (elements <= left_index(idx)) return 0;
			else if (elements > right_index(idx)) return 2;
			else return 1;
		}
};