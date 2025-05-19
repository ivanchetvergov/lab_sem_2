#pragma once
#include <iostream>
#include <cstring>

class ShortArray {
private:
    static constexpr size_t LOCAL_SIZE = 12; // под встр массив
    union {
        short* arr; // динам  
        short small_arr[LOCAL_SIZE]; // стат
    };

    struct {
        size_t arr_size : 63;   // размер массива
        size_t is_dynamic : 1; // 1  флаг динамического массива
    } data;

    size_t el = 0; // количество элементов

public:
    // кнструкторы
    ShortArray();
    ShortArray(size_t initial_size);
    ~ShortArray();

    // методы
    void push(short new_val);
    short pop();
    size_t size() const { return data.arr_size; }
    void resize(size_t new_size, short fill_value = 0);
    void resize();
    void print() const;

    // операторы
    short& operator[](size_t index);
    const short& operator[](size_t index) const;
    ShortArray& operator=(const ShortArray& other);

    bool get_is_dynamic() const { return data.is_dynamic; }
    void set_is_dynamic(bool value) { data.is_dynamic = value; }
};
