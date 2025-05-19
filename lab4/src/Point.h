#pragma once 
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

class Point {  
public:  
    // конструкторы  
    Point() : x(0), y(0) {}  
    Point(double x, double y) : x(x), y(y) {}  

    // геттеры
    double get_x() const { return x; }
    double get_y() const { return y; }  

private:  
    double x, y;  
};

class Circle : public Point {  
public:  
    // конструкторы  
    Circle() : Point(), radius(0) {}  
    Circle(double x, double y, double r) : Point(x, y), radius(std::abs(r)) {}  

    // геттер
    double get_radius() const { return radius; }

    //методы
    double square() const {  return radius * radius * 3.14; }
    void print() const { cout << "radius: " << radius << " center dot(x, y): (" << get_x() << ", " <<get_y() << ")\n";}

private:  
    double radius;  
};  