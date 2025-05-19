#pragma once
#include <iostream>

class Rect {
private:
    int dot_x, dot_y, width, height;

    int m_bottom = dot_y;
    int m_left = dot_x;
    int m_top = m_bottom + height;
    int m_right = m_left + width;

public:
    void print(); // вывод

    int get_left(); // вывод левой
    int get_right(); // вывод правой
    int get_top(); // вывод вверх
    int get_bottom(); // вывод низ

    int get_width(); // вывод ширины
    int get_height(); // вывод высоты

    int get_square(); // вывод площади

    void set_all(int dot_x, int dot_y, int width, int height); // инициализация методом
    //void set_all(int left, int bottom, int right, int top); // инициализация методом
    void set_height(int n);
    void set_width(int n);

    Rect(); // дефолтный конструктор (нули)
    Rect(int dot_x, int dot_y, int width, int height) ; // пользовательский конструктор
    //Rect(int left, int bottom, int right, int top) ; // пользовательский конструктор
    Rect(const Rect& main); // конструктор копирования

    ~Rect(); // деструктор


    void move(int dx = 0, int dy = 0); // сдвиг

    void Inflate(int n); // увеличить все стороны на n
    void Inflate(int n, int m); //увеличить ширину на n высоту на m
    void Inflate(int a, int b, int c, int d);

    void GetAll(int &left, int &right, int &top, int &bottom) const; // метод для "доставания" из привата
};

int input(); // ввод числа

Rect bounding_rect(Rect r1, Rect r2); // поиск наименьшего

void print_rect(Rect &r); // ф-ия вывода





