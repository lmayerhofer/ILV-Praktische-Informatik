/*
 * Aufgabe 1_1 - Testprogramm
 * Lukas Mayerhofer
 * 27.10.12
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "heap.cpp"

int main() {
	std::cout << "\nBEISPIEL 2:\n";

	std::cout << "\nSortierter Heap:";
	std::cout << "\n================================================================================\n";

	Heap<int> testInt(6);

	testInt.push(3);
	testInt.push(1);
	testInt.push(4);
	testInt.push(11);
	testInt.push(7);
	testInt.push(8);

	std::cout << "\n1. 6 Werte mit Heap::push hinzugefügt: testInt.push({3,1,4,11,7,8});";

	std::cout << "\n\nAusgabe (unsortiert):";
	std::cout << "\n--------------------------------------------------------------------------------";
	testInt.print();

	std::cout << "\nAusgabe (sortiert):";
	std::cout << "\n--------------------------------------------------------------------------------\n";
	testInt.sort();
	std::cout << std::endl;
}