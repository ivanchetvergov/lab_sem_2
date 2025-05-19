#include "BoolArray.h"
#include <cstring>  

BoolArray::BytesControl BoolArray::BytesControl::operator=(bool value) {
	std::cout << "IM WORKING\n";
    if (value) { byte |= (1 << bit_index); }
    else { byte &= ~(1 << bit_index); } 
    return *this;  
}

BoolArray::BoolArray(size_t size_given) : size_(size_given) {
    data = new uint8_t[(size_given + 7) / 8]{};
}

BoolArray::BoolArray(size_t size_given, bool arg) : size_(size_given) {
    data = new uint8_t[(size_given + 7) / 8];
    std::memset(data, arg ? 0xFF : 0, (size_given + 7) / 8);
}

BoolArray::BoolArray(const BoolArray& other) : size_(other.size_) {
    data = new uint8_t[(size_ + 7) / 8];
    std::memcpy(data, other.data, (size_ + 7) / 8);
}

BoolArray::~BoolArray() {
    delete[] data;
}

void BoolArray::resize(size_t size_given, bool arg) {  
    if (size_given <= 0) throw std::out_of_range("resize out");  

    uint8_t* new_data = new uint8_t[(size_given + 7) / 8];  
    std::memset(new_data, 0, (size_given + 7) / 8); 
 
    size_t copy_size = (size_given < size_) ? size_given : size_;  
    for (size_t i = 0; i < copy_size; ++i) {    
        if (data[i / 8] & (1 << (i % 8))) {  
            new_data[i / 8] |= (1 << (i % 8)); 
        }  
    }  
 
    for (size_t i = copy_size; i < size_given; ++i) {  
        if (arg) {  
            new_data[i / 8] |= (1 << (i % 8));  
        }
    }  

    delete[] data;  
    data = new_data;
    size_ = size_given;
}


BoolArray& BoolArray::operator=(const BoolArray& other) {
    if (this == &other) return *this;

    delete[] data;
    size_ = other.size_;
    data = new uint8_t[(size_ + 7) / 8];
    std::memcpy(data, other.data, (size_ + 7) / 8);
    return *this;
}

bool BoolArray::operator[](size_t index) const {
    if (index >= size_) throw std::out_of_range("out of");
    return (data[index / 8] >> (index % 8)) & 1;
}

BoolArray::BytesControl BoolArray::operator[](size_t index) {
    if (index >= size_) throw std::out_of_range("out of");
    return BytesControl(data[index / 8], index % 8);
}

void BoolArray::print() const {  
    for (size_t i = 0; i < size_; ++i) {  
        bool bit = (*this)[i];
        std::cout << bit;  
    }
    std::cout << std::endl;  
}
