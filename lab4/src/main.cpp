#include "Point.h"
#include "List.h"
#include "../../lab1/src/myString.h"

#include <iostream>

using std::cout;
using std::endl;

int main(){
	Circle c(2, 2, 2);
	Point p(3.6, -1.2);

	List list;
	list.push_back(c);

	for (int i = 0; i < 10; ++i){
		if (i % 2 == 0){
			list.push_front(Circle(1. * i, 1. * i, 1. * i));
		}
		if (i % 2 == 1){
			list.push_back(Circle(-1. * i, -1. * i, -1. * i));
		}
	}
	cout << "\n----------NOT SORTED----------\n\n";
	list.print();
	cout << "------------SORTED------------\n\n";
	list.sort();
	list.print();
	cout << "-----------POP BOTH-----------\n\n";
	list.pop_front();
	list.pop_back();
	list.print();
	cout << "------------DELETE------------\n\n";
	cout << "delete el (0, 0, 0) " << list.delete_el(Circle(0, 0, 0)) << endl;
	cout << "delete el (4, 4, 4): " << list.delete_el(Circle(4, 4, 4)) << endl;
	cout << "delete all el (2, 2, 2): " << list.delete_all_el(Circle(2, 2, 2)) << endl;
	cout << list;
	list.saveToFile("file.txt");
	cout << "read\n";
	list.loadFromFile("file.txt");
	cout << list;
	return 0;
}