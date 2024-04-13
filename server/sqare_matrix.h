#pragma once
#include"number.h"
#include"matrix.h"

class SqareMatrix : public Matrix
{
public:
    // Перегрузка оператора присваивания
    SqareMatrix& operator=(Matrix& other);

    //Конструктор класса по умолчанию
    SqareMatrix();
    //Конструктор класса для инициализации матрицы
    SqareMatrix(int n);

    //Деструктор класса явно объявлять не требуется, так как автоматически вызвается деструктор класса родителя, в котором у нас динамическое выделение памяти!

    //Вычисление детерминанта
    number calculateDetermenant();
    //Получить размерность матрицы
    int getDimension();
};
