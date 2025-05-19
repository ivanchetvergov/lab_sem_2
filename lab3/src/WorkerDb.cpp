#include "WorkerDb.h"

WorkerData& WorkerDb::operator[](const MyString& lastName) {  
	if (workers.find(lastName) == workers.end()) {  
	   	workers[lastName] = WorkerData(MyString(), 0); // заглушка
	}   
    return workers[lastName];  
} 

WorkerDb::Iterator& WorkerDb::Iterator::operator++() {
    ++it;
    return *this;
}

void print_db(WorkerDb& db){
	for (auto it = db.begin(); it != db.end(); ++it){
		std::cout << it.key() << " -> " << it->name << ", " << it->age << " years\n";
	}
}

double get_avg_age(WorkerDb& db) {
    size_t count = 0;
    int total_age = 0;

    for (auto it = db.begin(); it != db.end(); ++it) {
        total_age += it->age;
        ++count;
    }

    return count > 0 ? static_cast<double>(total_age) / count : 0.0;
}