#include "wrapper.h"
#include <cstring>  // Для strtok
#include <string>
#include <iomanip>  // Для std::setw

TextWrapper::TextWrapper(const MyString& input, int width) : text(input), line_width(width) {}

void TextWrapper::printBorder(char borderChar) const {
    std::cout << " " << std::string(line_width + 2, borderChar) << "\n";
}

void TextWrapper::printWrappedText() const {
    char* inputCopy = new char[text.length() + 1]; // Делаем копию строки, так как strtok изменяет её
    std::strcpy(inputCopy, text.c_str());

    char* word = std::strtok(inputCopy, " ");
    int currentLen = 0, line = 1;

    while (word != nullptr) {
        int wordLen = std::strlen(word);
        
        if (currentLen + wordLen + 1 > line_width) {
            std::cout << std::setw(line_width - currentLen) << std::setfill(' ') << " \\" << "\n";
            std::cout << "| ";
            currentLen = 0;
            line++;
        }

        if (currentLen == 0) {
            std::cout << (line == 1 ? "\\ " : "| ");
        }

        std::cout << word << " ";
        currentLen += wordLen + 1;
        word = std::strtok(nullptr, " ");
    }

    if (currentLen > 0) {
        std::cout << std::setw(line_width - currentLen) << std::setfill(' ') << " /" << "\n";
    }

    delete[] inputCopy;
}

void TextWrapper::printCat() const {
    std::cout << "     \\\n";
    std::cout << "      \\\n";
    std::cout << "       /\\_/\\  (\n";
    std::cout << "      ( ^.^ ) _)\n";
    std::cout << "        \\\"/  (\n";
    std::cout << "      ( | | )\n";
    std::cout << "     (__d b__)\n";
}

void TextWrapper::print_wrapped() const {
    printBorder('_');
    printWrappedText();
    printBorder('-');
    printCat();
}
