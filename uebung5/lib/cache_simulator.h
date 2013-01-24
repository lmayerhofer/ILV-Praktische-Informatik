#ifndef CACHE_SIMULATOR
#define CACHE_SIMULATOR

#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>

#include "ring_buffer.h"

using namespace std;

class CacheSimulator {

public:
	enum Organization {DIRECT_MAPPED = 1, FULLY_ASSOCIATIVE = 2, SET_ASSOCIATIVE = 3};
	
	//
	//
	//
	CacheSimulator(unsigned cs, unsigned cls, Organization org, unsigned ss=1, unsigned al=64) : cache_size(cs), cache_line_size(cls), organization(org), set_size(ss), address_length(al) {
		
		hits = 0;
		misses = 0;

		// Anzahl der Cachelines berechnen
		no_cache_lines = cache_size / cache_line_size / set_size;
		
		// Länge des Offsets
		lo_offset = log(cache_line_size) / log(2);
		
		// Länge des Index; wenn "fully assoc", dann kein Index
		if (organization==FULLY_ASSOCIATIVE) {
			lo_index = 0;
		}
		else {
			lo_index = log(no_cache_lines) / log(2);
		}
		
		// Länge des Tags berechnen
		lo_tag = address_length - lo_offset - lo_index;
		
		// Offset-Maske erstellen
		lo_offset_mask = 0x00;
		for (unsigned i=0; i<lo_offset; i++) {
			lo_offset_mask <<= 1;
			lo_offset_mask = lo_offset_mask | 0x01;
		}
		
		// Index-Maske erstellen
		lo_index_mask = 0x00;
		for (unsigned i=0; i<lo_index; i++) {
			lo_index_mask <<= 1;
			lo_index_mask = lo_index_mask | 0x01;
		}
		
		// Struktur für Index/Tag initialisieren (=>Array aus RingBuffern)
		cache = new RingBuffer[no_cache_lines];
		for(unsigned i=0; i<no_cache_lines; i++) {
			cache[i].set_size(set_size);
		}
		
		// Eine leere Maske für die einzelnen Cachelines generieren
		string cache_line_mask = "";
		for (unsigned i=0; i<cache_line_size; i++) {
			cache_line_mask.append("0");
		}

		// die einzelnen Cachelines mit der leeren Maske befüllen
		cache_lines.resize(no_cache_lines * set_size);
		for (unsigned i=0; i<no_cache_lines*set_size; i++) {
			cache_lines[i] = cache_line_mask;
		}

		cout << "Cache: " << organization << endl;
		cout << "no_cache_lines: " << no_cache_lines << endl;
		cout << "cache_line_size: " << cache_line_size << endl;
		cout << "lo_offset: " << lo_offset << endl;
		cout << "lo_index: " << lo_index << endl;
		cout << "lo_tag: " << lo_tag << endl;
		cout << "set_size: " << set_size << endl << endl;
		
	}
	~CacheSimulator(){}
	
	bool handle_address(string address, unsigned &tag, unsigned &index, unsigned &offset) {
		
		static unsigned counter = 0;

		counter++;

		// zu kurze Adressen mit 0 auffüllen
		while(address.length() < (address_length / 4)) {
			address = "0" + address;
		}
		
		long unsigned bin_address;
		
		istringstream(address) >> hex >> bin_address;
		
		offset = bin_address & lo_offset_mask;
		bin_address >>= lo_offset;
		
		index = bin_address & lo_index_mask;
		bin_address >>= lo_index;
		
		tag = bin_address;
		
		printf("(%d) %lx - %x - %x\n", counter, bin_address, index, offset);

		return !out_of_bound_error(index);
	}
	
	void new_instruction(string address, unsigned size) {
		unsigned tag;
		unsigned index;
		unsigned offset;
		
		if (!handle_address(address, tag, index, offset)) return;
		
		check_hit_or_miss(tag, index, offset);
		// cout << "I " << address << " " << bin_address << "\n";
	}
	
	void new_store(string address, unsigned size) {
		unsigned tag;
		unsigned index;
		unsigned offset;
		
		if (!handle_address(address, tag, index, offset)) return;

		cache[index].push(tag);
	}
	
	void new_load(string address, unsigned size) {
		unsigned tag;
		unsigned index;
		unsigned offset;
		
		if (!handle_address(address, tag, index, offset)) return;
		
		bool hit = false;

		int tag_index = cache[index].find(tag);
		unsigned cache_line_index = 0;

		if (tag_index >= 0) {
			cache_line_index = (index * set_size + tag_index) -1;

			cout << "at offset: " << cache_lines[cache_line_index][offset] << endl;
			if (cache_lines[cache_line_index][offset]=='1') {
				hits++;
				hit = true;
			}
		}
		if(!hit) {
			misses++;
			tag_index = cache[index].push(tag);
			cache_line_index = (index * set_size + tag_index) - 1;

			if (cache_line_index==0) {
				cout << "i: " << index << " * ss: " << set_size << " + ti: " << tag_index << " -1" << endl;
			}
			
			/*cout << "cli: " << cache_line_index << endl;
			cout << "tag_index: " << tag_index << endl;
			cout << "index: " << index << " / size: " << size << " / offset: " << offset << endl;
			cout << "gibt: " << (int)(cache_line_size-(size - 1 + offset)) << endl;*/

			if ((int)(cache_line_size-(size - 1 + offset)) < 0) {
				cout << "end of the line" << endl;
				while(size > 0) {
					if (cache_line_index>(no_cache_lines*set_size)) {
						cout << "Out of bounds: Too much data for my little cache :-(" << endl;
						throw;
					}
					while(size > 0 && offset<cache_line_size) {
						cout << cache_lines[cache_line_index].size() << " VS " << offset << endl;
						cache_lines[cache_line_index][offset] = '1';
						offset++;
						size--;
					}
					offset = 0;
					cache_line_index++;
				}
			} 
			else {
				cout << "--------------------------------------------------------------------->" << offset << " / " << cache_line_index << endl;
				cout << "at offset: " << cache_lines[cache_line_index][offset] << endl;
				for (unsigned i=0; i<size; i++) {
					cache_lines[cache_line_index][offset+i] = '1';
				}
			}
		}
	}
	
	void new_modify(string address, unsigned size) {
		unsigned tag;
		unsigned index;
		unsigned offset;
		
		if (!handle_address(address, tag, index, offset)) return;
		
		check_hit_or_miss(tag, index, offset);
	}
	
	void check_hit_or_miss(unsigned tag, unsigned index, unsigned offset) {
		
		// TODO: offset & iterieren bei längeren inserts
		
	}

	bool out_of_bound_error(unsigned index) {
		if (index > no_cache_lines) {
			cout << "Error: Array out of bound: "<< index << " / " << no_cache_lines << endl;
			return true;
		}
		else return false;
	}
	
	float get_misses_percent() const {
		if (misses + hits ==0)
			return 0.0;

		return ((float)misses / ((float)hits + (float)misses)) * 100;
		//return 0.0;
	}

	float get_hits_percent() const {
		if (misses + hits ==0)
			return 0.0;

		return ((float)hits / (hits + misses)) * 100;
		//return 0.0;
	}

	unsigned get_hits() const {
		return hits;
	}
	
	unsigned get_misses() const {
		return misses;
	}
	
	void print_cache_lines() const {
		for(unsigned i=0; i < no_cache_lines*set_size; i++) {
			cout << cache_lines[i] << endl;
		}
	}


private:

	// Struktur für Index/Tag
	RingBuffer *cache;
	
	// Struktur für tatsächliche Cachelines
	vector<string> cache_lines;

	unsigned cache_size;
	unsigned cache_line_size;
	unsigned no_cache_lines;
	Organization organization;
	unsigned set_size;
	unsigned address_length;
	
	unsigned lo_tag;
	unsigned lo_index;
	unsigned lo_offset;
	
	int lo_offset_mask;
	int lo_index_mask;
	
	unsigned hits;
	unsigned misses;
};

#endif
