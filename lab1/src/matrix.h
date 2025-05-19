#pragma once

#include <iostream>

class Matrix{
private:
	unsigned int rows, cols;
	double** matrix;

public:
	// конструкторы
	Matrix(int n); // квадратная размером n
	Matrix(int m, int n, double fill_value = 0); // размером m x n
	Matrix(const Matrix& main); // копирования
	

	Matrix& operator=(const Matrix& other); // присваивания
	Matrix& operator+=(const Matrix& other); // сложение
	Matrix& operator-=(const Matrix& other); // вычитание
	Matrix& operator*=(const Matrix& other); // умножение

	Matrix& operator*=(const double value); // умножение
	Matrix& operator/=(const double value); // деление

	Matrix operator+(const Matrix& other) const; // сложение
	Matrix operator-(const Matrix& other) const; // вычитание
	Matrix operator*(const Matrix& other) const; // умножение
	Matrix operator*(const double value) const; // вычитание
	Matrix operator/(const double value) const; // вычитание

	// мув
	Matrix& operator=(Matrix&& other);

	~Matrix(); // деконструктор

	void print(); // вывод

	// методы
	double get(int i, int j) const; // получить эл
	void set(int i, int j, double value); // установить знач эл
	int get_height(); // высота
	int get_width(); // ширина
	void negate(); // операция `-A` для матрицы
	void add_in_place(const Matrix &other); // операция `this += other
	Matrix multiply(const Matrix &other); // возвращает результат матричного умножения
	Matrix inverse() const;
};

// глобальные перегрузки
Matrix operator*(double scalar, const Matrix& matrix);
Matrix operator-(const Matrix& matrix);