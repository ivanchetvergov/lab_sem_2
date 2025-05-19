#include "ShortArray.h"
#include <stdexcept>
#include <iostream>
// конструкторы
ShortArray::ShortArray() {
    data.arr_size = LOCAL_SIZE;
    set_is_dynamic(false);
}

ShortArray::ShortArray(size_t initial_size) {
    data.arr_size = initial_size;
    if (initial_size > LOCAL_SIZE) {
        arr = new short[initial_size];
        set_is_dynamic(true);
    } else {
        set_is_dynamic(false);
    }
}

// Деструктор
ShortArray::~ShortArray() {  
    if (get_is_dynamic()) { delete[] arr; }  
}

// Добавление элемента
void ShortArray::push(short new_val) {
    if (el == size()) { resize(); }
    if (get_is_dynamic()) { arr[el] = new_val; }
    else { small_arr[el] = new_val; }
    ++el;
}

short ShortArray::pop() {
    if (el == 0) {
        throw std::out_of_range("array is empty");
    }
    // Сохраняем удаляемый элемент
    short value = get_is_dynamic() ? arr[el - 1] : small_arr[el - 1];
    --el;  // Уменьшаем количество элементов

    if (get_is_dynamic() && el <= LOCAL_SIZE) {
        // создаем временную копию перед удалением arr
        short* temp = new short[el];
        std::copy(arr, arr + el, temp);

        // теперь копируем temp в small_arr
        std::copy(temp, temp + el, small_arr);
        delete[] temp;
        set_is_dynamic(false);
    } else if (get_is_dynamic()) {
        // уменьшаем динамический массив
        short* temp = new short[el];
        std::copy(arr, arr + el, temp);
        delete[] arr;
        arr = temp;
    }

    return value;
}


void ShortArray::resize(size_t new_size, short fill_value) {
    if (new_size == 0) {
        throw std::out_of_range("wrong size");
    }

    if (new_size <= LOCAL_SIZE && get_is_dynamic()) {
        // с дин массива на встр
        // создаем темп (копия ар)
        short* temp = new short[new_size];
        std::copy(arr, arr + new_size, temp);
        // переносим из темп в смол ар
        std::copy(temp, temp + new_size, small_arr);
        set_is_dynamic(false);
    } else if (new_size > LOCAL_SIZE && !get_is_dynamic()) {
        // с встр на дин
        // темп копия смол ар
        short* temp = new short[new_size];
        std::copy(small_arr, small_arr + el, temp);

        arr = temp;
        set_is_dynamic(true);
    } else if (get_is_dynamic()) {
        // изменение размера динамического массива
        short* temp = new short[new_size];
        std::copy(arr, arr + el, temp);
        delete[] arr;
        arr = temp;
    }

    // заполняем
    for (size_t i = el; i < new_size; ++i) {
        if (get_is_dynamic()) arr[i] = fill_value;
        else small_arr[i] = fill_value;
    }
    
    el = new_size;
    data.arr_size = new_size;
}

short& ShortArray::operator[](size_t index) {
    if (index >= el) throw std::out_of_range("Index out of range");
    return get_is_dynamic() ? arr[index] : small_arr[index];
}

const short& ShortArray::operator[](size_t index) const {
    if (index >= el) throw std::out_of_range("Index out of range");
    return get_is_dynamic() ? arr[index] : small_arr[index];
}

ShortArray& ShortArray::operator=(const ShortArray& other) {
    if (this == &other) return *this;

    if (get_is_dynamic()) delete[] arr;

    el = other.el;
    data.arr_size = other.data.arr_size;
    set_is_dynamic(other.get_is_dynamic());

    if (get_is_dynamic()) {
        arr = new short[data.arr_size];
        std::memcpy(arr, other.arr, sizeof(short) * el);
    } else {
        std::memcpy(small_arr, other.small_arr, sizeof(short) * el);
    }

    return *this;
}

void ShortArray::print() const {
    for (size_t i = 0; i < el; ++i) {
        std::cout << (get_is_dynamic() ? arr[i] : small_arr[i]) << " ";
    }
    std::cout << std::endl;
}

void ShortArray::resize() {
    resize(data.arr_size * 2); 
}
