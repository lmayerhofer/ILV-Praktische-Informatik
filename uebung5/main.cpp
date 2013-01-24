#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "lib/cache_simulator.h"
#include "lib/cache_simulator_manager.h"

// I ... read
// S ... store
// L ... load
// M ... modify

int main (int argc, char *argv[]) {
	
	CacheSimulator instruction_cache(128, 32, CacheSimulator::DIRECT_MAPPED);
	CacheSimulator data_cache(128, 32, CacheSimulator::DIRECT_MAPPED);
	CacheSimulatorManager cs_manager(instruction_cache, data_cache);
	
	std::string line;
	
	// keine Filename beim Aufruf, deshalb
	// schauen, ob über stdin was kommt
	if (argc==1) {
		while (std::getline(std::cin, line)) {
			cs_manager.handle_line(line);
		}
	}
	// Übergebene Datei öffnen und 
	// Zeile für Zeile einlesen
	else {
		std::ifstream infile(argv[1]);
		
		while (std::getline(infile, line)) {
			cs_manager.handle_line(line);
		}
	}
	
	cs_manager.print_stats();
	
	return 0;
}
