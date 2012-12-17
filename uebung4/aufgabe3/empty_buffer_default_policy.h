#ifndef EMPTYBUFFERDEFAULTPOLICY_H
#define EMPTYBUFFERDEFAULTPOLICY_H

template <class T> class EmptyBufferDefaultPolicy {
	protected:
		T empty(T defaultElement = NULL) {
			return defaultElement;
		}
};

#endif