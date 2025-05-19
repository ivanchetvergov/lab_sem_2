#pragma once
#include <iostream>

class MyString {
private:
    char* data;   // указатель на строку
    size_t size;  // длина строки

    void free_memory(); // вспомогательный метод для освобождения памяти

public:
    // конструкторы
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);

    // деструктор
    ~MyString();

    // move
    MyString& operator=(MyString&& other) noexcept;

    // операторы присваивания и изменения
    MyString& operator=(const MyString& other);
    MyString& operator+=(const MyString& other);
    MyString& operator+=(const char* str);

    // операторы сравнения (не изменяют объект, поэтому const)
    bool operator<(const MyString& other) const;
    bool operator<(const char* str) const;

    bool operator<=(const MyString& other) const;
    bool operator<=(const char* str) const;

    bool operator==(const MyString& other) const;
    bool operator==(const char* str) const;

    bool operator!=(const MyString& other) const;
    bool operator!=(const char* str) const;

    // методы
    char get(int i) const;
    void set(int i, char c);
    void set_new_string(const char* str);
    void print() const;
    void read_line();

    size_t length() const { return size; }
    const char* c_str() const { return data; }

    char& operator[](size_t index);
    const char& operator[](size_t index) const;  

    static MyString from_int(int num);

    // глобальные перегрузки
    friend MyString operator+(const MyString& left, const MyString& right);
    friend MyString operator+(const MyString& left, const char* right);
    friend MyString operator+(const char* left, const MyString& right);

    friend bool operator<(const char* left, const MyString& right);
    friend bool operator<=(const char* left, const MyString& right);
    friend bool operator==(const char* left, const MyString& right);
    friend bool operator!=(const char* left, const MyString& right);
    
    friend std::ostream& operator<<(std::ostream& stream, const MyString& str);
    friend std::istream& operator>>(std::istream& stream, MyString& str);
};
