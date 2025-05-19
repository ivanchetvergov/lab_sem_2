#include "BaseFile.h"
#include <cstring>
#include <iostream>
#include <vector>
#include <cmath>

RleFile::RleFile(const char* path, const char* mode) 
    : BaseFile(path, mode) ,buffer(nullptr), bufferSize(0), bufferPos(0){
        // std::cout << "constructor RleFile(path, mode)\n";
    }

RleFile::~RleFile() {
    if (buffer) {  
    delete[] buffer;  
    buffer = nullptr; // предотвращаем двойное освобождение  
    }
}

size_t RleFile::rle_encoded_size(const char* data, size_t size) {  
    size_t encoded_size = 0;  
    size_t i = 0;  

    while (i < size) {  
        size_t count = 1;  
        while (i + count < size && data[i] == data[i + count] && count < 255)   
            count++;  

        encoded_size += 2; // (счётчик + символ)  
        i += count;   
    }  
    return encoded_size;  
}  

size_t RleFile::rle_encode(const char* data, size_t size, char* dst) {  
    size_t dst_index = 0;  
    size_t i = 0;  

    while (i < size) {  
        size_t count = 1;  
        while (i + count < size && data[i] == data[i + count] && count < 255)  
            count++;  

        dst[dst_index++] = static_cast<char>(count);  
        dst[dst_index++] = data[i];  

        i += count;  
    }  
    return dst_index;  
}


size_t RleFile::rle_decoded_size(const char* encoded, size_t encoded_size) {
    size_t decoded_size = 0;
    for (size_t i = 0; i < encoded_size; i += 2) {
        decoded_size += static_cast<unsigned char>(encoded[i]); 
    }
    return decoded_size;
}


size_t RleFile::rle_decode(const char* encoded, size_t encoded_size, char* dst) {  
    size_t dst_index = 0;  

    for (size_t i = 0; i < encoded_size; i += 2) {  

        unsigned char count = static_cast<unsigned char>(encoded[i]);  
        char value = encoded[i + 1];  

        // заполняем buf значениями  
        memset(dst + dst_index, value, count);  
        dst_index += count;  
    }  

    return dst_index;  
}


size_t RleFile::write(const void* buf, size_t n_bytes) {
    if (!buf || n_bytes == 0) return 0;

    size_t encoded_size = rle_encoded_size(static_cast<const char*>(buf), n_bytes);
    char* encoded = new char[encoded_size];

    encoded_size = rle_encode(static_cast<const char*>(buf), n_bytes, encoded);
    size_t written = write_raw(encoded, encoded_size);  

    delete[] encoded;
    return written;
}

// TODO: происходит переполнение `buf`: завести внутренний буфер, в котором будет маленький кусочек читаемого файла
//       писать в buf из этого буфера не больше, чем max_bytes
size_t RleFile::read(void* buf, size_t max_bytes) {  
    if (!buf || max_bytes == 0) return 0;  

    // нужно записывать новые дданные в буфер 
    if (bufferPos >= bufferSize) {  
        size_t encoded_size = get_file_size(); // размер закод
        char* encoded = new char[encoded_size]; // массив закод
        size_t bytesRead = read_raw(encoded, encoded_size); // читаем

        if (bytesRead == 0) { // проверка чтения
            delete[] encoded;  
            return 0;  
        }

        delete[] buffer; // очищаем старые данные из буфера
        bufferPos = 0;  // поз начало буфера     

        size_t decoded_size = rle_decoded_size(encoded, bytesRead);  
        buffer = new char[decoded_size]; // выделяем память под новый буфер
        bufferSize = decoded_size; // размерность массива

        rle_decode(encoded, bytesRead, buffer); // декодируем в бафер  
        delete[] encoded;  

    }  

    // копируем не больше `max_bytes` из внутреннего буфера  
    size_t bytesToCopy = std::min(max_bytes, bufferSize - bufferPos);  
    memcpy(buf, buffer + bufferPos, bytesToCopy);  
    bufferPos += bytesToCopy; // обновляем текущюю поз буфера  

    return bytesToCopy;  
}

// size_t RleFile::read(void* buf, size_t max_bytes) {  
//     if (!buf || max_bytes == 0) return 0;  

//     char* buffer = nullptr;    

//     size_t encoded_size = get_file_size();  
//     char* encoded = new char[encoded_size];

//     size_t bytesRead = read_raw(encoded, encoded_size);  
//     if (bytesRead == 0) {  
//         delete[] encoded;  
//         return 0;  
//     }  

//     size_t decoded_size = rle_decoded_size(encoded, bytesRead);  
//     buffer = new char[decoded_size];  

//     rle_decode(encoded, bytesRead, buffer);   

//     // копируем не больше `max_bytes` из внутреннего буфера  
//     size_t bytesToCopy = std::min(max_bytes, decoded_size);  
//     memcpy(buf, buffer, bytesToCopy);    

//     delete[] encoded; 
//     delete[] buffer;
//     return bytesToCopy;  
// }

//Rle2

size_t RleFile2::get_file_size() const{
    return wrappedFile->get_file_size();
}

size_t RleFile2::write(const void* buf, size_t n_bytes) {
    if (!buf || n_bytes == 0) return 0;

    size_t encoded_size = RleFile::rle_encoded_size(static_cast<const char*>(buf), n_bytes);
    char* encoded = new char[encoded_size];

    encoded_size = RleFile::rle_encode(static_cast<const char*>(buf), n_bytes, encoded);
    size_t written = wrappedFile->write(encoded, encoded_size);  

    delete[] encoded;
    return written;   
}

size_t RleFile2::read(void* buf, size_t max_bytes) {
    if (!buf || max_bytes == 0) return 0;  

    // нужно записывать новые дданные в буфер 
    if (bufferPos >= bufferSize) {  
        size_t encoded_size = wrappedFile->get_file_size(); // размер закод
        char* encoded = new char[encoded_size]; // массив закод
        size_t bytesRead = wrappedFile->read(encoded, encoded_size); // читаем

        if (bytesRead == 0) { // проверка чтения
            delete[] encoded;  
            return 0;  
        }

        delete[] buffer; // очищаем старые данные из буфера
        bufferPos = 0;  // поз начало буфера     

        size_t decoded_size = RleFile::rle_decoded_size(encoded, bytesRead);  
        buffer = new char[decoded_size]; // выделяем память под новый буфер
        bufferSize = decoded_size; // размерность массива

        RleFile::rle_decode(encoded, bytesRead, buffer); // декодируем в бафер  
        delete[] encoded;  

    }  

    // копируем не больше `max_bytes` из внутреннего буфера  
    size_t bytesToCopy = std::min(max_bytes, bufferSize - bufferPos);  
    memcpy(buf, buffer + bufferPos, bytesToCopy);  
    bufferPos += bytesToCopy; // обновляем текущюю поз буфера  

    return bytesToCopy;  
}

// size_t RleFile2::read(void* buf, size_t max_bytes) {
//     if (!buf || max_bytes == 0) return 0;

//     size_t encoded_size = wrappedFile->get_file_size();
//     if (encoded_size == 0) return 0;

//     char* encoded = new char[encoded_size];
//     size_t bytesRead = wrappedFile->read(encoded, encoded_size);

//     if (bytesRead == 0) {
//         delete[] encoded;
//         return 0;
//     }

//     size_t decoded_size = RleFile::rle_decoded_size(encoded, bytesRead);
//     char* decoded = new char[decoded_size + 1];

//     decoded_size = RleFile::rle_decode(encoded, bytesRead, decoded);
//     memcpy(buf, decoded, decoded_size);
//     static_cast<char*>(buf)[decoded_size] = '\0';

//     delete[] encoded;
//     delete[] decoded;
//     return decoded_size;
// }


