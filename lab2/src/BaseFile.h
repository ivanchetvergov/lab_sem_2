#pragma once
#include <cstdio>

class IFile {
public:
    virtual bool can_read() const = 0;
    virtual bool can_write() const = 0;
    virtual size_t write(const void* buf, size_t n_bytes) = 0;
    virtual size_t read(void* buf, size_t max_bytes) = 0;
    virtual size_t get_file_size() const = 0;
    virtual ~IFile() {};
};

class BaseFile : public IFile {
private:
    FILE* file;
    char* mode; 

public:
    // конструкторы
    BaseFile();
    BaseFile(const char* path, const char* mode);
    BaseFile(FILE* existingFile);

    // деструктор
    virtual ~BaseFile();

    // методы
    bool is_open() const;
    bool can_read() const;
    bool can_write() const;

    bool seek(long offset);
    long tell() const;

    // запретили 
    BaseFile(const BaseFile&) = delete;
    BaseFile& operator=(const BaseFile&) = delete;

    // мув 
    BaseFile(BaseFile&& other) noexcept;
    BaseFile& operator=(BaseFile&& other) noexcept;

    virtual size_t write_raw(const void* buf, size_t n_bytes);
    virtual size_t read_raw(void* buf, size_t max_bytes);

    // прикольчик
    virtual size_t write(const void* buf, size_t n_bytes);
    virtual size_t read(void* buf, size_t max_bytes);

    void reopen(const char* path, const char* mode);
    size_t get_file_size() const override;

    // вспомогательные ф-ии
    FILE* get_file() { return file; };
    char* getFileOpenMode() const { return mode; }

};

class BaseFile32 : public BaseFile {
private:
    const char* encodingTable;  // указатель на таблицу кодировки
    static constexpr char defaultTable[33] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
    char* buffer;    
    size_t bufferSize; // размерчик буфера       
    size_t bufferPos;  // текущая позиция чтения в буфере  

public:
    // конструктор
    BaseFile32(const char* path, const char* mode, const char* table);
    BaseFile32(const char* path, const char* mode);

    ~BaseFile32() override;

    // определение размеров кодированных и декодированных данных
    static int encoded32_size(int raw_size);
    static int decoded32_size(int encode_size);
    
    // кодирование и декодирование base32
    static int encode32(const char* raw_data, int raw_size, char* dst);
    static int decode32(const char* encoded_data, int encoded_size, char* dst);

    // переопределенные методы
    size_t write(const void* buf, size_t n_bytes) override;
    size_t read(void* buf, size_t max_bytes) override;
};

class Base2File32 : public IFile {
private:
    IFile* wrappedFile; 
    char* buffer;    
    size_t bufferSize; // размерчик буфера       
    size_t bufferPos;  // текущая позиция чтения в буфере  

public:
    Base2File32(IFile* file) : wrappedFile(file), buffer(nullptr), \
    bufferSize(0), bufferPos(0) {}

    ~Base2File32() override { 
        delete wrappedFile;
        delete[] buffer;
     }

    bool can_read() const override { return wrappedFile->can_read(); }
    bool can_write() const override { return wrappedFile->can_write(); }

    size_t write(const void* buf, size_t n_bytes) override;
    size_t read(void* buf, size_t max_bytes) override;
    size_t get_file_size() const override;
};




class RleFile : public BaseFile {
private:
    char* buffer;    
    size_t bufferSize; // размерчик буфера       
    size_t bufferPos;  // текущая позиция чтения в буфере  

public:

    RleFile(const char* path, const char* mode);
    ~RleFile() override;

    static size_t rle_encoded_size(const char* data, size_t size);
    static size_t rle_encode(const char* data, size_t size, char* dst);

    static size_t rle_decoded_size(const char* encoded, size_t encoded_size);
    static size_t rle_decode(const char* encoded, size_t encoded_size, char* dst);

    // переопределенные методы
    size_t write(const void* buf, size_t n_bytes) override;
    size_t read(void* buf, size_t max_bytes) override;
};

class RleFile2 : public IFile {
private:
    IFile* wrappedFile;
    char* buffer;    
    size_t bufferSize; // размерчик буфера       
    size_t bufferPos;  // текущая позиция чтения в буфере  

public:
    RleFile2(IFile* file) : wrappedFile(file), buffer(nullptr), bufferSize(0), bufferPos(0) {}

    ~RleFile2() override { 
        delete wrappedFile;
        delete[] buffer;
    }

    bool can_read() const override { return wrappedFile->can_read(); }
    bool can_write() const override { return wrappedFile->can_write(); }

    size_t write(const void* buf, size_t n_bytes) override;
    size_t read(void* buf, size_t max_bytes) override;
    size_t get_file_size() const override;
};

    