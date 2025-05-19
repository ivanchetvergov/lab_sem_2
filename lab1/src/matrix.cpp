#include "matrix.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Matrix& Matrix::operator=(Matrix&& other) {
    if (this != &other) {  
        delete[] matrix;  

        rows = other.rows;
        cols = other.cols;
        matrix = other.matrix;  

        other.matrix = nullptr; 
        other.rows = 0;
        other.cols = 0;
    }
    return *this;
}



Matrix operator*(double scalar, const Matrix& matrix) {
    Matrix result = matrix;  
    return result * scalar;  
}

Matrix operator-(const Matrix& matrix) {
    Matrix result = matrix;  
    result.negate();
    return result;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols){
        std::cerr << "err + \n";
    }

    Matrix result(rows, cols, 0);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows ||  cols != other.cols){
        std::cerr << "err - \n";
    }

    Matrix result(rows, cols, 0);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator/(const double value) const {
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.matrix[i][j] = matrix[i][j] / value;
        }
    }
    return result;
}

Matrix Matrix::operator*(const double value) const {
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.matrix[i][j] = matrix[i][j] * value;
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (rows != other.cols){
        std::cerr << "err * \n";
    }

    Matrix result(rows, cols, 0);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            for (int k = 0; k < rows; ++k){
            result.matrix[i][j] = matrix[i][k] + other.matrix[k][j];               
            }
        }
    }
    return result;
}

Matrix& Matrix::operator=(const Matrix& other){
    if (this != &other) { 
        for (size_t i = 0; i < rows; ++i) {  
            delete[] matrix[i];  
        }  
        delete[] matrix;  

        this -> rows = other.rows;  
        this -> cols = other.cols;  
        matrix = new double*[rows];  
        for (size_t i = 0; i < rows; ++i) {  
            matrix[i] = new double[cols];  
            for (size_t j = 0; j < cols; ++j) {  
                matrix[i][j] = other.matrix[i][j];  
            }  
        }  
    }  
        return *this; 
}

Matrix& Matrix::operator+=(const Matrix& other){
    if (rows != other.rows || cols != other.cols){
        std::cerr << "error Matrix +=\n";
    }
    for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < cols; ++j)
        {
            matrix[i][j] += other.matrix[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other){
    if (rows != other.rows || cols != other.cols){
        std::cerr << "error Matrix -=\n";
    }
    for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < cols; ++j)
        {
            matrix[i][j] -= other.matrix[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other){
    *this = this->multiply(other);
    return *this;  
}

Matrix& Matrix::operator*=(const double value) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix[i][j] *= value;
        }
    }
    return *this;
}

Matrix& Matrix::operator/=(const double value) {
    if (value == 0) {
        std::cerr << "err val = 0 str71\n";
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix[i][j] /= value;
        }
    }
    return *this;
}

Matrix::Matrix(int n) : rows(n), cols(n) {
	// выделяем память для строк
    matrix = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        // выделяем память для столбцов в каждой строке
        matrix[i] = new double[cols];
        // инициализируем все элементы нулями
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(int m, int n, double fill_value) : rows(m), cols(n) {
    // выделяем память для строк
    matrix = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        // выделяем память для столбцов в каждой строке
        matrix[i] = new double[cols];
        // инициализируем все элементы заданным значением
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = fill_value;
        }
    }
}

//для глобальных операторов т.к они создают копию
Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    matrix = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new double[cols];
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = other.matrix[i][j]; 
        }
    }
}

Matrix::~Matrix() {
    if (matrix != nullptr) {  // проверяем, выделялась ли память
        for (int i = 0; i < rows; ++i) {
            if (matrix[i] != nullptr) {
                delete[] matrix[i]; // освобождаем память для каждой строки
            }
        }
        delete[] matrix; // освобождаем массив указателей
        matrix = nullptr; // защита от повторного освобождения
    }
}

void Matrix::print(){
	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < cols; ++j)
		{
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

double Matrix::get(int i, int j) const { return matrix[i][j]; } // взять значение

void Matrix::set(int i, int j, double value) { matrix[i][j] = value; } // установить знач ячейки

int Matrix::get_width() { return rows; } // вернуть высоту

int Matrix::get_height() { return cols; } // вернуть ширину

void Matrix::negate(){
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            matrix[i][j] *= - 1;
        }
    }
}

void Matrix::add_in_place(const Matrix& other) {
    // проверяем размерность
    if (rows != other.rows || cols != other.cols) {
        throw invalid_argument("size error");
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] += other.matrix[i][j];
        }
    }
}

Matrix Matrix::multiply(const Matrix &other) {  
    // проверяем размерность  
    if (cols != other.rows) {  
        throw invalid_argument("size error");  
    }  

    Matrix result(rows, other.cols);  // создаем результирующую матрицу

    // вычисления
    for (int i = 0; i < rows; ++i) {  
        for (int j = 0; j < other.cols; ++j) {  
            result.matrix[i][j] = 0; // инициализация для дальн суммы
            for (int k = 0; k < cols; ++k) {
                result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];  
            }  
        }  
    }  

    return result;  
}