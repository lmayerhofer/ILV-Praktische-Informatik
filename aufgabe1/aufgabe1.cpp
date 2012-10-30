/*
 * Aufgabe 1
 * Lukas Mayerhofer
 * 20.10.12
 */

#include "merge_lists.cpp"

intlist generate_numbers(int min, int step) {
    intlist list;
    for(int i=3*step+min; i>=min; i-=step) {
        list.push_back(i);
    }
    return list;
}

int main() {
    intlist::iterator it;
    intlist lists[4], list1, list2, list3, list4, result;

    list1 = generate_numbers(0,4);			// 0,4,8,12
    list2 = generate_numbers(1,4);			// 1,5,9,13
    list3 = generate_numbers(2,4);			// 2,6,10,14
    list4 = generate_numbers(3,4);			// 3,7,11,15
    
    // make list array (for merging and sorting)
    lists[0] = list1;
    lists[1] = list2;
    lists[2] = list3;
    lists[3] = list4; 
    
    // output each list
    std::cout << "1. list: ";
    for(it=list1.begin(); it!=list1.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n2. listl: ";
    for(it=list2.begin(); it!=list2.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n3. list: ";
    for(it=list3.begin(); it!=list3.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n4. list: ";
    for(it=list4.begin(); it!=list4.end(); ++it)
        std::cout << *it << " ";

    // output merged list
    result = merge_lists(lists,4);
    
    std::cout << "\n\nmerged list: ";
    for(it=result.begin(); it!=result.end(); ++it)
        std::cout << *it << " ";
    
    return 0;
}
