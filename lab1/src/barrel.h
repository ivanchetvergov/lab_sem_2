#pragma once

#include <iostream>

class Barrel {
private:
    double volume;   // объем бочки
    double alcohol;  // количество спирта

public:
    Barrel(double volume, double alcohol); // конструктор

    double getAlcoholConc() const; // текущая концентрация спирта в процентах

    void overflowFromTo(Barrel &other, double cupVolume); // перелить жидкость
};
