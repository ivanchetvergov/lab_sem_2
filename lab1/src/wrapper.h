#pragma once
#include <iostream>
#include <string>
#include "MyString.h"

class TextWrapper {
private:
    MyString text;
    int line_width;

    void printCat() const;
    void printBorder(char borderChar) const;
    void printWrappedText() const;

public:
    TextWrapper(const MyString& input, int width);
    void print_wrapped() const;
};
