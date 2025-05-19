#include "myRect.h"
#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

void Rect::print() {
    cout << "left: " << m_left << " right: " << m_right 
         << " top: " << m_top << " bottom: " << m_bottom << "\n";
}

int Rect::get_left() { return m_left; }  

int Rect::get_right() { return m_right; }  

int Rect::get_top() { return m_top; }  

int Rect::get_bottom() { return m_bottom; }

// нахождение наименьшего прямоуг
Rect bounding_rect(Rect r1, Rect r2){
    int left = min(r1.get_left(), r2.get_left());
    int right = max(r1.get_right(), r2.get_right());
    int bottom = min(r1.get_bottom(), r2.get_bottom());
    int top = max(r1.get_top(), r2.get_top());

    return Rect(left, right, bottom, top);
}

//вывод как функция, а не метод
void print_rect(Rect &r) {  
    cout <<"rect: \n"  
    << "left   = " << r.get_left() << "\n"  
    << "right  = " << r.get_right() << "\n"  
    << "top    = " << r.get_top() << "\n"  
    << "bottom = " << r.get_bottom() << "\n";  
}

// вывод высоты
//int Rect::get_height(){ return abs(m_top - m_bottom); }
int Rect::get_height(){ return height; }

// вывод ширины
//int Rect::get_width(){ return abs(m_right - m_left); }
int Rect::get_width(){ return width; }

/*void Rect::set_height(int n){
    m_top = abs(n);
    m_bottom = 0;
}*/
void Rect::set_height(int n) { height = n;}

/*void Rect::set_width(int n){
    m_right = abs(n);
    m_left = 0;
}*/
void Rect::set_width(int n) { width = n;}

// вывод площади
int Rect::get_square(){ return get_height() * get_width(); }

/*void Rect::set_all(int left, int bottom, int right, int top) {  
    m_left = left;  
    m_right = right;  
    m_top = top;  
    m_bottom = bottom; 
    cout << "data was recorded: (" << left << ", " << right 
         << ", " << top << ", " << bottom << ")\n";
}*/

void Rect::set_all(int dot_x, int dot_y, int width, int height) {  
    m_bottom = dot_y;
    m_left = dot_x;
    m_top = m_bottom + height;
    m_right = m_left + width;
    cout << "data was recorded(set all).\n";
} 

// метод для перемещения  
void Rect::move(int dx, int dy) {  
    m_left += dx; // перемещение по оси X  
    m_right += dx; // перемещение по оси X  
    m_top += dy; // перемещение по оси Y  
    m_bottom += dy; // перемещение по оси Y  
} 

//дефолтный (нулевой конструктор)
Rect::Rect() : dot_x(0), dot_y(0), height(0), width(0) {
    cout << "this is the default constructor\n";
}

//конструктор копирования
Rect::Rect(const Rect& main) {
    m_left = main.m_left;
    m_right = main.m_right;
    m_top = main.m_top;
    m_bottom = main.m_bottom;
}

//деструктор
Rect::~Rect(){
    //cout << "destructor works\n";
}

//конструктор инициализации
/*Rect::Rect(int left, int bottom, int right, int top) 
    : m_left(left), m_right(right), m_top(top), m_bottom(bottom) {
    cout << "data was recorded: (" << left << ", " << right 
         << ", " << top << ", " << bottom << ")\n";
}*/
Rect::Rect(int dot_x, int dot_y, int width, int height) 
    : dot_x(dot_x), dot_y(dot_y), width(width), height(height) {
    cout << "data was recorded(constructor).\n";
}

void Rect::GetAll(int &left, int &right, int &top, int &bottom) const {
    left = m_left;
    right = m_right;
    top = m_top;
    bottom = m_bottom;
}

void Rect::Inflate(int n) {
    m_left -= n;
    m_right += n;
    m_bottom -= n;
    m_top += n;
}

void Rect::Inflate(int n, int m) {
    m_left -= n;
    m_right += n;
    m_bottom -= m;
    m_top += m;
}

void Rect::Inflate(int a, int b, int c, int d) {
    m_left += a;
    m_right += b;
    m_bottom += c;
    m_top += d;
}

int input() {
    int userInput;
    cout << "enter your input: ";

    while (true) {
        cin >> userInput;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // пропускаем до новой строки
            cout << "incorrect input. try again: ";
        } else {
            //cout << "this is your input: " << userInput << '\n';
            break;
        }
    }
    return userInput;
}
