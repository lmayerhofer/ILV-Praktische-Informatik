/*
 * Aufgabe 1_1 - student.h
 * Lukas Mayerhofer
 * 27.10.12
 */

class Student {
	public:
		Student() { }
		Student(std::string n, unsigned a) : name(n), age(a) { }
		virtual ~Student() { }

		std::string GetName() const { return name; }
		unsigned GetAge() const { return age; }

		bool operator<(Student);
		
	private:
		std::string name;
		unsigned age;
};

// << Operator als globale Funktion
std::ostream& operator<<(std::ostream& Stream, const Student& s);	// const damit s nicht verändert werden kann

bool Student::operator<(Student s) {
	return this->age < s.GetAge();
}

std::ostream& operator<<(std::ostream& Stream, const Student& s) {
	return Stream << "[Name: " << s.GetName() << ", Alter: " << s.GetAge() << "]";
}