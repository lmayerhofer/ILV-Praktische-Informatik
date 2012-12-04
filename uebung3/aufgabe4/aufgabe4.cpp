#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>

#include "skipnode.h"
#include "skiplist.h"

using namespace std;

int main() {
    SkipList<int> list;
    list.print();

    list.insert(4);
    list.insert(9);
    list.insert(2);
    list.insert(7);
    list.insert(5);
    list.insert(1);
    list.insert(1);
    list.insert(3);
    
    if (list.search(7)) {
        cout << "7 is in the list\n";
    }

    /*list.insert(Student(1, "Lukas", 25));
    list.insert(Student(5, "Thomas", 20));
    list.insert(Student(3, "Karl", 22));
    list.insert(Student(2, "Stefan", 24));
    list.insert(Student(4, "Christoph", 31));
    list.insert(Student(1, "Sepp", 19));*/

    list.print();

    return 0;
}