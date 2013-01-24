#ifndef CACHE_SIMULATOR_MANAGER
#define CACHE_SIMULATOR_MANAGER

#include <stdio.h>
#include <stdlib.h>
#include "compact_vector.h"
#include "print_vector.h"
#include "split_string.h"

class CacheSimulatorManager {

public:
	//
	//
	//
	CacheSimulatorManager();
	CacheSimulatorManager(CacheSimulator ic, CacheSimulator dc) : instruction_cache(ic), data_cache(dc) {
		reads = 0;
		stores = 0;
		loads = 0;
		modifies = 0;
	}
	~CacheSimulatorManager(){}
	
	void handle_line(std::string line) {
		
		// komische Zeilen überspringen
		if (line=="x.x" || line.find('#')==0) return;
		
		std::string operation;
		std::string address;
		unsigned size;

		std::vector<std::string> parts = split_string(line, ' ');

		parts = compact_vector(parts);

		if (parts.size() == 2) {
			operation = parts[0];

			parts = split_string(parts[1], ',');

			if (parts.size() == 2) {
				address = parts[0];
				size = atoi(parts[1].c_str());
				
				if (operation =="I") {
					instruction_cache.new_instruction(address, size);
					reads++;
				}
				else if (operation == "S") {
					data_cache.new_store(address, size);
					stores++;
				}
				else if (operation == "L") {
					data_cache.new_load(address, size);
					loads++;
				}
				else if (operation == "M") {
					data_cache.new_modify(address, size);
					modifies++;
				}
			}
			else {
				throw(line.c_str());
			}
		}
		else {
			throw(line.c_str());
		}
	}
	
	void print_stats() const {
		cout << "reads: " << reads << "\n";
		cout << "stores: " << stores << "\n";
		cout << "loads: " << loads << "\n";
		cout << "modifies: " << modifies << "\n\n";
		
		cout << "Instruction cache: \n";
		cout << "hits: "   << instruction_cache.get_hits() << "(" << instruction_cache.get_hits_percent() << "%)\n";
		cout << "misses: " << instruction_cache.get_misses() << "(" << instruction_cache.get_misses_percent() << "%)\n\n";
		
		cout << "Data cache: \n";
		cout << "hits: "   << data_cache.get_hits() << "(" << data_cache.get_hits_percent() << "%)\n";
		cout << "misses: " << data_cache.get_misses() << "(" << data_cache.get_misses_percent() << "%)\n";

		data_cache.print_cache_lines();
	}
	
private:
	CacheSimulator instruction_cache;
	CacheSimulator data_cache;
	
	unsigned reads;
	unsigned stores;
	unsigned loads;
	unsigned modifies;
	
};

#endif
