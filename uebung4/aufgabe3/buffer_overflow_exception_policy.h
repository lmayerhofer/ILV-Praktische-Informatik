#ifndef BUFFEROVERFLOWEXCEPTIONPOLICY_H
#define BUFFEROVERFLOWEXCEPTIONPOLICY_H

template <class T> class BufferOverflowExceptionPolicy {
	public:
		class Exception: public std::exception {
			public:
				Exception() { }

				virtual const char *what() {
					return "\nException: Buffer overflow.";
				}
		};

	protected:
		void overflow(unsigned& start, unsigned& end, unsigned& max_size, T*& buffer, T new_element) {
			throw Exception();
		}
};

#endif