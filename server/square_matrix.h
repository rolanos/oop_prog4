#pragma once

#include"matrix.h"

#define DIMENSION 4
#define INITIAL_VALUE 0.0

template<class number>
class SqareMatrix : public Matrix<number>
{
public:
    // Перегрузка оператора присваивания
    SqareMatrix& operator=(Matrix<number>& other);

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

template<class number>
SqareMatrix<number>& SqareMatrix<number>::operator=(Matrix<number>& other)
{
    //Проверяем квадратная ли матрица
    if (other.isSqare()) {
        //При условии, если квадратная - берем количество строк = стороне матрицы
        int dimension = other.getRowNumber();
        if (dimension == this->dimension)
        {
            for (int i = 0; i < dimension; i++)
            {
                for (int j = 0; j < dimension; j++)
                {
                    this->inputValue(other(i, j), i, j);
                }
            }
        }
    }


    return *this;
}

template<class number>
SqareMatrix<number>::SqareMatrix() : Matrix<number>(DIMENSION, DIMENSION){}

template<class number>
SqareMatrix<number>::SqareMatrix(int n) : Matrix<number>(n, n) {}

template<class number>
number SqareMatrix<number>::calculateDetermenant() {

    number determenant = number(1, 1);
    SqareMatrix mat = SqareMatrix<number>(this->dimension);

    for (int i = 0; i < this->dimension; i++)
    {
        for (int j = 0; j < this->dimension; j++)
        {
            mat.inputValue((*this)(i, j), i, j);;
        }
    }
    for (int i = 0; i < this->dimension; i++) {
        int pivot = i;

        for (int j = i + 1; j < this->dimension; j++) {
            if (abs(mat(j, i)) > abs(mat(pivot, i))) {
                pivot = j;
            }
        }
        if (pivot != i) {
            mat.swapRows(i, pivot);
            determenant = determenant * (-1);
        }

        if (mat(i, i) == 0.0) {
            return number();
        }
        determenant = determenant * mat(i, i);

        for (int j = i + 1; j < this->dimension; j++) {
            number fact = mat(j, i) / mat(i, i);
            for (int k = i + 1; k < this->dimension; k++) {
                mat.inputValue(mat(j, k) - fact * mat(i, k), j, k);
            }
        }
    }
    return determenant;
}

template<class number>
    int SqareMatrix<number>::getDimension() {
    return this->dimension;
}

