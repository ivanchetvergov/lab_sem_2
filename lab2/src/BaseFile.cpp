#include "BaseFile.h"
#include <iostream>
#include <cstring>
#include <utility> 

using namespace std;

BaseFile::BaseFile(BaseFile&& other) noexcept
    : file(std::exchange(other.file, nullptr)), mode(std::exchange(other.mode, nullptr)) {}

BaseFile& BaseFile::operator=(BaseFile&& other) noexcept {
    if (this != &other) {
        if (file) fclose(file);
        delete[] mode;

        file = std::exchange(other.file, nullptr);
        mode = std::exchange(other.mode, nullptr);
    }
    return *this;
}

BaseFile::BaseFile() : file(nullptr), mode(nullptr){
    // cout << "constructor BaseFile()\n";
}

BaseFile::BaseFile(const char* path, const char* openMode) : file(nullptr), mode(nullptr) {
    file = fopen(path, openMode);
    if (file) {
        mode = strdup(openMode);
        if (!mode) {
            std::cerr << "error: BaseFile 12(mode)\n";
            fclose(file);
            file = nullptr;
        }
    } else {
        std::cerr << "error: BaseFile 17(open file)" << path << "\n";
    }
    // cout << "constructor BaseFile(path, mode)\n";
}

BaseFile::BaseFile(FILE* existingFile) : file(existingFile), mode(nullptr) {
    // cout << "constructor BaseFile(existingFile)\n";
}

BaseFile::~BaseFile() {
    if (file) fclose(file);
    if (mode) free(mode);
    // cout << "destructor BaseFile()\n";
}

void BaseFile::reopen(const char* path, const char* openMode) {
    if (file) fclose(file); 
    if (mode) free(mode);    

    file = fopen(path, openMode);
    if (file) {
        mode = strdup(openMode);
        if (!mode) {
            std::cerr << "error: BaseFile 38(mode)\n";
            fclose(file);
            file = nullptr;
        }
    } else {
        std::cerr << "error: BaseFile 43(open file)" << path << "\n";
    }
}

bool BaseFile::is_open() const {
    return file != nullptr;
}

bool BaseFile::can_read() const {
    return is_open() && mode && (strchr(mode, 'r') != nullptr);
}

bool BaseFile::can_write() const {
    return is_open() && mode && (strchr(mode, 'w') != nullptr || strchr(mode, 'a') != nullptr);
}

size_t BaseFile::write_raw(const void* buf, size_t n_bytes) {
    if (!can_write()) {
        std::cerr << "error: BaseFile 65(write_raw)\n";
        return 0;
    }
    return fwrite(buf, 1, n_bytes, file);
}

size_t BaseFile::read_raw(void* buf, size_t max_bytes) {
    if (!can_read()) {
        std::cerr << "error: BaseFile 74(can't read)\n";
        return 0;
    }
    size_t read_bytes = fread(buf, 1, max_bytes, file);
    return read_bytes;
}

long BaseFile::tell() const {
    return is_open() ? ftell(file) : -1;
}

bool BaseFile::seek(long offset) {
    return is_open() && (fseek(file, offset, SEEK_SET) == 0);
}

size_t BaseFile::write(const void* buf, size_t n_bytes) {
    return write_raw(buf, n_bytes);
}

size_t BaseFile::read(void* buf, size_t max_bytes) {
    return read_raw(buf, max_bytes);
}

size_t BaseFile::get_file_size() const {
    if (!is_open()) return 0;
    
    long current_pos = ftell(file);  
    fseek(file, 0, SEEK_END);

    size_t size = ftell(file);        
    fseek(file, current_pos, SEEK_SET);  

    return size;
}
