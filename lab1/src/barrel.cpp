#include "barrel.h"
#include <iostream>
#include <limits>

using namespace std;

// конструктор
Barrel::Barrel(double volume, double alcohol)
    : volume(volume), alcohol(alcohol) {}

// метод для получения концентрации спирта
double Barrel::getAlcoholConc() const {
    return (alcohol / volume) * 100; // концентрация в процентах
}

// переливание из другой бочки
void Barrel::overflowFromTo(Barrel &other, double cupVolume) {
    // проверка на возможное переполнение или отрицательное значение
    if (cupVolume > other.volume || cupVolume < 0) {
        std::cerr << "объем кружки превышает объем другой бочки или некорректен\n";
        return;
    }

    // рассчитываем количество спирта в переданной жидкости
    double alcoholTrans = (other.alcohol / other.volume) * cupVolume;

    // обновляем данные о другой бочке
    other.volume -= cupVolume;
    other.alcohol -= alcoholTrans;

    // обновляем данные о текущей бочке
    this->volume += cupVolume;
    this->alcohol += alcoholTrans;
}
