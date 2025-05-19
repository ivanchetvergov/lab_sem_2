#pragma once
#include "../../lab1/src/myString.h"
#include <map>   
#include <iostream>  

struct WorkerData {  
    MyString name;  
    int age;  

    WorkerData(const MyString& name, int age) : name(name), age(age) {};
    WorkerData() : name(MyString()), age(0) {};
};  

struct WorkerDb {  

	WorkerDb() = default;

    WorkerData& operator[](const MyString& lastName); 


    struct Iterator {

    	Iterator(std::map<MyString, WorkerData>::iterator iter) : it(iter) {}

    	WorkerData& operator*() { return it->second; }

    	WorkerData* operator->() { return &(it->second); }

    	Iterator& operator++();

    	bool operator!=(const Iterator& other) const { return it != other.it; }

    	MyString key() const { return it->first; }


    private:
    	std::map<MyString, WorkerData>::iterator it;
    };

    Iterator begin() { return Iterator(workers.begin()); }
    Iterator end() { return Iterator(workers.end()); }


private:  
    std::map<MyString, WorkerData> workers; // фамилия инфа
};  

void print_db(WorkerDb&);
double get_avg_age(WorkerDb& db);