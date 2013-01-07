#ifndef COMPACT_VECTOR
#define COMPACT_VECTOR

#include <vector>

using namespace std;

//
// entfernt leere Einträge aus einem Vector: ["", "", "ein", "", "String"] => ["ein", "String"]
//
vector<string> compact_vector(vector<string> vec) {
	vector<int> goners;
	
	for (unsigned i=0; i<vec.size(); i++) {
		if (vec.at(i)=="") {
			goners.push_back(i);
		}
	}
	for(unsigned i=0; i<goners.size(); i++) {
		vec.erase(vec.begin()+goners[i]-i);
	}
	
	return vec;
}

#endif
