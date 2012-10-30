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
	std::cout << "\nBEISPIEL 1:\n";

	// Heap mit Datentyp <int>
	std::cout << "\nTest mit Datentyp <int>:";
	std::cout << "\n================================================================================";

	//Heap<int> testInt(10);
	Heap<int> testInt(10);
	std::cout << "\n1. Heap mit 10 Elementen erstellt: Heap<int> testInt(10);";

	testInt.push(3);
	testInt.push(1);
	testInt.push(4);
	testInt.push(15);
	testInt.push(6);
	testInt.push(5);
	testInt.push(10);
	testInt.push(10);
	testInt.push(9);
	testInt.push(8);
	std::cout << "\n2. 10 Werte mit Heap::push hinzugefügt: testInt.push({3,1,4,15,6,5,10,10,9,8});";

	// Heap kopieren für Beispiel 2 - Heap Sort
	//Heap<int> test2Int = testInt;

	std::cout << "\n\nAusgabe:";
	std::cout << "\n--------------------------------------------------------------------------------";
	testInt.print();

	for(int i = 0; i < 6; i++) {
		testInt.pop();
	}
	std::cout << "\n3. 6 Elemente mit Heap::pop gelöscht: testInt.pop();";
	
	std::cout << "\n\nAusgabe:";
	std::cout << "\n--------------------------------------------------------------------------------";
	testInt.print();

	// Heap mit eigenem Datentyp <Student>
	std::cout << "\nTest mit eigenem Datentyp (=Klasse) <Student>:";
	std::cout << "\n================================================================================";
	Heap<Student> testStudent(5);

	testStudent.push(Student("Lukas", 25));
	testStudent.push(Student("Thomas", 23));
	testStudent.push(Student("Simon", 24));
	testStudent.push(Student("Markus", 22));
	testStudent.push(Student("Max", 18));
	std::cout << "\n1. 5 Studenten hinzugefügt: testStudent.push(Student(<string>,<int>));";

	std::cout << "\n\nAusgabe:";
	std::cout << "\n--------------------------------------------------------------------------------";
	testStudent.print();

	for(int i = 0; i < 2; i++) {
		testInt.pop();
	}
	std::cout << "\n2. 2 Elemente mit Heap::pop gelöscht: testStudent.pop();";
	
	std::cout << "\n\nAusgabe:";
	std::cout << "\n--------------------------------------------------------------------------------";
	testStudent.print();
}