#ifndef EMPTYBUFFEREXCEPTIONPOLICY_H
#define EMPTYBUFFEREXCEPTIONPOLICY_H

template <class T> class EmptyBufferExceptionPolicy {
	public:
		class Exception: public std::exception {
			public:
				Exception() { }

				virtual const char *what() {
					return "\nException: Buffer is empty";
				}
		};

	protected:
		T empty() {
			throw Exception();
		}
};

#endif