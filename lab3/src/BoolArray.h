#pragma once
#include <iostream>
#include <cstdint>  
#include <stdexcept>

struct BoolArray {
 
    BoolArray(size_t size_given);
    BoolArray(size_t size_given, bool arg);
    BoolArray(const BoolArray& other);
    ~BoolArray();

    void print() const;
    size_t size() const { return size_; }
    void resize(size_t size_given, bool arg);

    // управление битиками
    struct BytesControl {

        BytesControl(uint8_t& byte_ref, size_t index) : byte(byte_ref), bit_index(index) {}

        operator bool() const { return (byte >> bit_index) & 1;  }
        BytesControl operator=(bool value);
        BytesControl operator=(const BytesControl& other) { return *this = static_cast<bool>(other); }
    private:
        uint8_t& byte;
        size_t bit_index;
    };

    // перегрузка операторов
    BoolArray& operator=(const BoolArray& other);
    bool operator[](size_t index) const; // чтение
    BytesControl operator[](size_t index); // измен

private:
    uint8_t* data;
    size_t size_;
};
