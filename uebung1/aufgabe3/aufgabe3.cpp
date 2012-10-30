/*
 * Aufgabe 1_1 - Testprogramm
 * Lukas Mayerhofer
 * 27.10.12
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "BinaryTree.h"
#include "AvlTree.cpp"

int main() {
	std::cout << "\nBEISPIEL 3:\n";

	std::cout << "\nn Zufallszahlen in binären Suchbaum einfügen:";
	std::cout << "\n================================================================================\n";

	int n = 0;

	for(int i = 1; i <= 5; i++) {
		n = i * 10000;
		std::cout << "\nn = " << n;
		std::cout << "\n--------------------------------------------------------------------------------\n";

		BinaryTree testBinary;
		AvlTree testAvl;
		for(int i = 0; i < n; i++) {
			testBinary.insert(rand());
			testAvl.insert(rand());
		}
		
		std::cout << "Höhe (Binary): " << testBinary.getHeight() << std::endl;
		std::cout << "Höhe (AVL): " << testAvl.getHeight() << std::endl;
	}
}