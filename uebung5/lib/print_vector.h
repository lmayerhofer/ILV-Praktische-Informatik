#ifndef PRINT_VECTOR
#define PRINT_VECTOR

#include <vector>

using namespace std;

void print_vector(vector<string> vec) {
	cout << "Vector: ";
	for(unsigned i=0; i<vec.size(); i++) {
		cout <<  " '" <<vec[i] << "' ";
	}
	cout << "\n";
}

#endif
