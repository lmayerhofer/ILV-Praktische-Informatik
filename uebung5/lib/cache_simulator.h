#ifndef CACHE_SIMULATOR
#define CACHE_SIMULATOR

#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

class CacheSimulator {

public:
	enum Organization {DIRECT_MAPPED = 1, FULLY_ASSOCIATIVE = 2, SET_ASSOCIATIVE = 3};
	
	//
	//
	//
	CacheSimulator(unsigned cs, unsigned cls, Organization org, unsigned ss=1, unsigned al=32) : cache_size(cs), cache_line_size(cls), organization(org), set_size(ss), address_length(al) {
		
		unsigned no_cache_lines = cache_size / cache_line_size;
		
		lo_offset = log(address_length) / log(2);
		
		switch(organization){
			case DIRECT_MAPPED: 
				lo_index = log(no_cache_lines) / log(2);
				break;
			case FULLY_ASSOCIATIVE:
				lo_index = 0;
				break;
			case SET_ASSOCIATIVE:
				lo_index = (log(no_cache_lines / set_size) / log(2));
				
				break;
		}
		
		lo_tag = address_length - lo_offset - lo_index;
		
		cout << "Cache: " << organization << "\n";
		cout << "lo_offset: " << lo_offset << "\n";
		cout << "lo_index: " << lo_index << "\n";
		cout << "lo_tag: " << lo_tag << "\n\n";
		
	}
	~CacheSimulator(){}
	
	void handle_address(string address, string &tag, string &index, string &offset) {
		string bin_address = hex2bin(address);
		
		tag    = bin_address.substr(0, lo_tag);
		index  = bin_address.substr(lo_tag-1, lo_index);
		offset = bin_address.substr(lo_tag+lo_index-1, lo_offset);
		
		cout << "Tag: " << tag << " - Index: " << index << " - Offset: " << offset << "\n";
	}
	
	void new_instruction(string address, unsigned size) {
		string tag;
		string index;
		string offset;
		
		handle_address(address, tag, index, offset);
		
		if(cache[index][tag]==1){
			hits++;
		}
		else {
			misses++;
		}
		
		// cout << "I " << address << " " << bin_address << "\n";
	}
	
	void new_store(string address, unsigned size) {
		string tag;
		string index;
		string offset;
		
		handle_address(address, tag, index, offset);
		
		cache[index][tag] = 1;
	}
	
	void new_load(string address, unsigned size) {
		string tag;
		string index;
		string offset;
		
		handle_address(address, tag, index, offset);
		
		if(cache[index][tag]==1){
			hits++;
		}
		else {
			misses++;
		}
	}
	
	void new_modify(string address, unsigned size) {
		string tag;
		string index;
		string offset;
		
		handle_address(address, tag, index, offset);
		
		if(cache[index][tag]==1){
			hits++;
		}
		else {
			misses++;
		}
	}
	
	// void print_cache() const {
	// 	typedef map<string, int> inner_map;
	// 	typedef map<string, inner_map > outer_map;
	// 	
	// 	
	// 	for(outer_map::iterator i = cache.begin(); i != cache.end(); i++) {
	// 		cout << i->first << "\n";
	// 		
	// 		inner_map &im = i->second;
	// 		
	// 		for(inner_map::iterator j = im.begin(); j != im.end(); j++) {
	// 			cout << "   " << j->first << "\n";
	// 		}
	// 	}
	// }
	
	unsigned get_hits() const {
		return hits;
	}
	
	unsigned get_misses() const {
		return misses;
	}
	
private:
	map<string, map<string, int> > cache;
	
	unsigned cache_size;
	unsigned cache_line_size;
	Organization organization;
	unsigned set_size;
	unsigned address_length;
	
	unsigned lo_tag;
	unsigned lo_index;
	unsigned lo_offset;
	
	unsigned hits;
	unsigned misses;
	
	map<string, unsigned> no_used_cache_lines;
	
	string hex2bin(string address) {
		string str = "";
		for (unsigned i = 0; i < address.length(); ++i) {
			switch (address [i]) {
				case '0': str.append ("0000"); break;
				case '1': str.append ("0001"); break;
				case '2': str.append ("0010"); break;
				case '3': str.append ("0011"); break;
				case '4': str.append ("0100"); break;
				case '5': str.append ("0101"); break;
				case '6': str.append ("0110"); break;
				case '7': str.append ("0111"); break;
				case '8': str.append ("1000"); break;
				case '9': str.append ("1001"); break;
				case 'a': str.append ("1010"); break;
				case 'b': str.append ("1011"); break;
				case 'c': str.append ("1100"); break;
				case 'd': str.append ("1101"); break;
				case 'e': str.append ("1110"); break;
				case 'f': str.append ("1111"); break;
			}
		}
		return str;
	}
	
};

#endif
