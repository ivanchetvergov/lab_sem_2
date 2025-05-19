#include "other.h"
#include "BaseFile.h"
#include <iostream>
#include <cstring>
#include "../../lab1/src/myString.h"  

void write_number(BaseFile* file, int number) {
    if (!file || !file->is_open()) {
        std::cerr << "err\n";
        return;
    }

    MyString num_str(std::to_string(number).c_str());

    if (number < 0) {  
        file->write("-", 1);
        num_str = MyString(num_str.c_str() + 1);
    }

    file->write(num_str.c_str(), num_str.length());
}

void write_int(BaseFile &file, int n) {
    MyString num_str = MyString::from_int(n);  
    file.write(num_str.c_str(), num_str.length()); 
}

void write_int(IFile &file, int n){
    MyString num_str = MyString::from_int(n);  
    file.write(num_str.c_str(), num_str.length()); 
}
