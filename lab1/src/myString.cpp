#include <iostream>
#include <cstring>
#include <string>
#include "myString.h"
#include <limits> 
#include <stdexcept>

using namespace std;

// move
MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const MyString& other){
    stream << other.c_str();
    return stream;
}

std::istream& operator>>(std::istream& stream, MyString& str) {
    char buffer[1024];
    stream.getline(buffer, sizeof(buffer));  
    str.set_new_string(buffer);
    return stream;
}

char& MyString::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("out of range");
    }
    return data[index];
}

const char& MyString::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("out of range");
    }
    return data[index];
}

bool operator<(const char* left, const MyString& right) {  
    return strcmp(left, right.data) < 0;  
}  

bool operator<=(const char* left, const MyString& right) {  
    return strcmp(left, right.data) <= 0;  
}  

bool operator==(const char* left, const MyString& right) {  
    return strcmp(left, right.data) == 0;   
}  

bool operator!=(const char* left, const MyString& right) {  
    return strcmp(left, right.data) != 0;  
}

bool MyString::operator<(const MyString& other) const {  
    return strcmp(data, other.data) < 0;  
}  

bool MyString::operator<(const char* str) const {  
    return strcmp(data, str) < 0;  
}  

bool MyString::operator<=(const MyString& other) const {  
    return strcmp(data, other.data) <= 0;  
}  

bool MyString::operator<=(const char* str) const {  
    return strcmp(data, str) <= 0;  
}  

bool MyString::operator==(const MyString& other) const {  
    return strcmp(data, other.data) == 0;  
}  

bool MyString::operator==(const char* str) const {  
    return strcmp(data, str) == 0;  
}  


bool MyString::operator!=(const MyString& other) const {  
    return strcmp(data, other.data) != 0;  
}  

bool MyString::operator!=(const char* str) const {  
    return strcmp(data, str) != 0;  
}  

MyString& MyString::operator+=(const MyString& other){ 
    if (this == &other) { return *this; } // проверка на самоприсваивание

    size_t newSize = size + other.size;
    char* newData = new char[newSize + 1];
    if (data) { strcpy(newData, data); }

    strcpy(newData + size, other.data);
    free_memory();
    data = newData;
    size = newSize;
    return *this;
}

MyString& MyString::operator+=(const char* str){
    MyString temp(str);
    return *this += temp;
}

MyString operator+(const MyString& left, const MyString& right){
    MyString temp(left);
    temp += right;
    return temp;
}

MyString operator+(const MyString& left, const char* right){
    MyString temp(right);
    return left + temp;
}

MyString operator+(const char* left, const MyString& right){
    MyString temp(left);
    return temp + right;
}

// освобождение памяти
void MyString::free_memory() {
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
        size = 0;
    }
}

// конструктор по умолчанию
MyString::MyString() : data(nullptr), size(0) {}

// конструктор с параметром
MyString::MyString(const char* str) {
    if (str != nullptr) {
        size = strlen(str);
        data = new char[size + 1]; // +1 для символа '\0'
        strcpy(data, str);
    } else {
        data = nullptr;
        size = 0;
    }
}

// конструктор копирования
MyString::MyString(const MyString& other) : size(other.size) {
    if (other.data != nullptr) {
        data = new char[size + 1]; // выделяем память для строки
        strcpy(data, other.data); // копируем строку
    } else {
        data = nullptr;
    }
}

// оператор присваивания
MyString& MyString::operator=(const MyString& other) {
    if (this == &other) {
        return *this; // проверяем на самоприсваивание
    }

    free_memory(); // освобождаем старую память

    size = other.size;
    if (other.data != nullptr) {
        data = new char[size + 1]; // выделяем память для строки
        strcpy(data, other.data); // копируем строку
    } else {
        data = nullptr;
    }

    return *this;
}

// деструктор
MyString::~MyString() {
    free_memory(); // освобождаем память при уничтожении объекта
}

// получение i-го символа строки
char MyString::get(int i) const {
    if (i < 0 || i >= static_cast<int>(size)) {
        throw std::out_of_range("out of range");
    }
    return data[i];
}

MyString MyString::from_int(int num) {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d", num);
    return MyString(buffer);
}

// установка i-го символа строки
void MyString::set(int i, char c) {
    if (i < 0 || i >= static_cast<int>(size)) {
        throw std::out_of_range("out of range");
    }
    data[i] = c;
}

// замена строки
void MyString::set_new_string(const char* str) {
    free_memory(); // освобождаем текущую строку

    if (str != nullptr) {
        size = strlen(str);
        data = new char[size + 1]; // +1 для '\0'
        strcpy(data, str);
    } else {
        data = nullptr;
        size = 0;
    }
}

// вывод строки на консоль
void MyString::print() const {
    if (data != nullptr) {
        cout << data << "\n";
    } else {
        cout << "empty row\n";
    }
}

void MyString::read_line() {
    free_memory(); // освобождаем текущую строку

    string input;

    if (cin.peek() == '\n') cin.ignore(); // Игнорируем \n только если он там есть

    if (!getline(cin, input)) {
        std::cerr << "error\n";
        return;
    }

    size = input.length();
    data = new char[size + 1];
    std::strcpy(data, input.c_str());
}


 




