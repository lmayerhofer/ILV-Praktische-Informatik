using namespace std;

class Student {
	public:
		Student() { }
		Student(unsigned i, string n, unsigned a) : id(i), name(n), age(a) { }
		virtual ~Student() { }

		unsigned GetId() const { return id; }
		string GetName() const { return name; }
		unsigned GetAge() const { return age; }

		bool operator<(Student);
		bool operator==(Student);
		bool operator!=(Student);
		
	private:
		unsigned id;
		string name;
		unsigned age;
};

// << Operator als globale Funktion
ostream& operator<<(ostream& Stream, const Student& s);	// const damit s nicht verändert werden kann

bool Student::operator<(Student s) {
	return this->id < s.GetId();
}

bool Student::operator==(Student s) {
	return this->id == s.GetId();
}

bool Student::operator!=(Student s) {
	return this->id != s.GetId();
}

ostream& operator<<(ostream& Stream, const Student& s) {
	return Stream << "[ID: " << s.GetId() << ", Name: " << s.GetName() << ", Alter: " << s.GetAge() << "]";
}