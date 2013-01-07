#ifndef SPLIT_STRING
#define SPLIT_STRING

#include <vector>

using namespace std;

//
// wandelt einen String in einen Vector um: "das ist ein string" => ["das", "ist", "ein", "string"]
//
vector<string> split_string(string str, char delimiter) {
	vector<string> tokens;
	
	size_t last_found = 0;
	size_t found = str.find(delimiter);
	string token;
	
	while(found != string::npos) {
		
		token = str.substr(last_found, found-last_found);
		tokens.push_back(token);
		
		last_found = found+1;
		found = str.find(delimiter, found+1);
	}
	
	token = str.substr(last_found, str.length()-last_found);
	tokens.push_back(token);
	
	return tokens;
}

#endif
