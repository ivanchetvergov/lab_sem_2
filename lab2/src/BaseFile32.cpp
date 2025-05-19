#include "BaseFile.h"
#include <cstring>
#include <iostream>

BaseFile32::BaseFile32(const char* path, const char* mode, const char* table) 
    : BaseFile(path, mode), encodingTable(table ? table : defaultTable), buffer(nullptr), bufferSize(0), bufferPos(0)  {
    // std::cout << "constructor BaseFile32(path, mode, table)\n";
}

BaseFile32::~BaseFile32() { 
    if (buffer) {  
        delete[] buffer;  
        buffer = nullptr; // предотвращаем двойное освобождение  
    }
} 

BaseFile32::BaseFile32(const char* path, const char* mode) 
    : BaseFile(path, mode), encodingTable(defaultTable),  buffer(nullptr), bufferSize(0), bufferPos(0) {
    // std::cout << "constructor BaseFile32(path, mode)\n";    
}

int BaseFile32::encoded32_size(int raw_size) 
{
    int bits = raw_size * 8;
    int remainder = bits % 5;

    int additional_bits = (remainder == 0) ? 0 : (5 - remainder);
    
    return (bits + additional_bits) / 5; 
}

// кодирование перед записью
size_t BaseFile32::write(const void* buf, size_t n_bytes) {
    int encoded_size = encoded32_size(n_bytes);
    char* encoded = new char[encoded_size + 1];
    if (!encoded) return 0;

    BaseFile32::encode32(static_cast<const char*>(buf), n_bytes, encoded);
    encoded[encoded_size] = '\0'; 

    size_t written = write_raw(encoded, encoded_size);
    delete[] encoded;
    return written;
}
    
size_t BaseFile32::read(void* buf, size_t max_bytes) {  
    char* encoded = new char[max_bytes + 1];

    size_t bytesRead = read_raw(encoded, max_bytes);  

    if (bytesRead == 0) {  
        delete[] encoded;  
        return 0;  
    }  

    encoded[bytesRead] = '\0';

    int decoded_size = decoded32_size(bytesRead);  
    char* decoded = new char[decoded_size + 1];

    BaseFile32::decode32(encoded, bytesRead, decoded);  

    size_t copy_size = std::min((size_t)decoded_size, max_bytes);  
    std::memcpy(buf, decoded, copy_size);  

    delete[] encoded;  
    delete[] decoded;  
    return copy_size;
} 

int BaseFile32::decoded32_size(int encode_size) 
{
    return (encode_size * 5) / 8; 
}

const char Table[33] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                                'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                                'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6'};

int BaseFile32::encode32(const char* raw_data, int raw_size, char* dst) 
{
    if (!raw_data || raw_size <= 0 || !dst) return 1;
    
    int bitCount = 0, buffer = 0, dstIndex = 0;
    
    for (int i = 0; i < raw_size; ++i) 
    {
        buffer = (buffer << 8) | static_cast<unsigned char>(raw_data[i]);
        bitCount += 8;

        while (bitCount >= 5) 
        {
            dst[dstIndex++] = Table[(buffer >> (bitCount - 5)) & 0x1F];
            bitCount -= 5;
        }
    }

    if (bitCount > 0) 
    {
        dst[dstIndex++] = Table[(buffer << (5 - bitCount)) & 0x1F];
    }

    dst[dstIndex] = '\0';
    return 0;
}

int BaseFile32::decode32(const char* encoded_data, int encoded_size, char* dst) 
{
    if (!encoded_data || encoded_size <= 0 || !dst) return 1;
    
    std::memset(dst, 0, BaseFile32::decoded32_size(encoded_size) + 1);
    
    int bit_pos = 0, byte_pos = 0;
    for (int i = 0; i < encoded_size; i++) 
    {
        int value = -1;
        for (int j = 0; j < 32; ++j) 
        {
            if (Table[j] == encoded_data[i]) 
            {
                value = j;
                break;
            }
        }

        if (value == -1) return 2;

        for (int bit = 4; bit >= 0; bit--) 
        {
            int bit_val = (value >> bit) & 1;
            dst[byte_pos] |= (bit_val << (7 - bit_pos));
            ++bit_pos;
            if (bit_pos == 8) 
            {
                bit_pos = 0;
                ++byte_pos;
            }
        }
    }
    dst[byte_pos] = '\0';
    return 0;
}

size_t Base2File32::get_file_size() const {
    return wrappedFile->get_file_size();
}

size_t Base2File32::write(const void* buf, size_t n_bytes) {
    int encoded_size = BaseFile32::encoded32_size(n_bytes);
    char* encoded = new char[encoded_size + 1]; // +1 для \0
    if (!encoded) return 0;

    BaseFile32::encode32(static_cast<const char*>(buf), n_bytes, encoded);
    encoded[encoded_size] = '\0'; // Гарантируем, что строка завершается \0
    
    size_t written = wrappedFile->write(encoded, encoded_size);
    delete[] encoded;
    return written;
}
    
// size_t Base2File32::read(void* buf, size_t max_bytes) {
//     char* encoded = new char[max_bytes + 1];
//     if (!encoded) return 0;

//     size_t bytesRead = wrappedFile->read(encoded, max_bytes);
    
//     int decoded_size = BaseFile32::decoded32_size(bytesRead);
//     char* decoded = new char[BaseFile32::decoded32_size(decoded_size) + 1];
//     encoded[bytesRead] = '\0';


//     BaseFile32::decode32(encoded, bytesRead, decoded);
//     std::memcpy(buf, decoded, decoded_size);

//     delete[] encoded;
//     delete[] decoded;
//     return decoded_size;
// }

size_t Base2File32::read(void* buf, size_t max_bytes) {  
    if (!buf || max_bytes == 0) return 0;  

    if (bufferPos >= bufferSize) {  
        size_t encoded_size = wrappedFile->get_file_size(); // размер закод  
        char* encoded = new char[encoded_size]; // массив закод  
        size_t bytesRead = wrappedFile->read(encoded, encoded_size); // читаем  

        if (bytesRead == 0) { // проверка чтения  
            delete[] encoded;  
            return 0;  
        }  

        delete[] buffer; // очищаем старые данные из буфера  
        bufferPos = 0;  // позиция начала буфера     

        size_t decoded_size = BaseFile32::decoded32_size(bytesRead);  
        buffer = new char[decoded_size]; // выделяем память под новый буфер  
        bufferSize = decoded_size; // размерность массива  

        BaseFile32::decode32(encoded, bytesRead, buffer); // декодируем в буфер  
        delete[] encoded;  
    }  

    size_t bytesToCopy = std::min(max_bytes, bufferSize - bufferPos);  
    memcpy(buf, buffer + bufferPos, bytesToCopy);  
    bufferPos += bytesToCopy; // обновляем текущую позицию в буфере  

    return bytesToCopy;  
}     



   
