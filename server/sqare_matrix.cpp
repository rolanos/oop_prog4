#include"sqare_matrix.h"

#define DIMENSION 4
#define INITIAL_VALUE 0.0

SqareMatrix& SqareMatrix::operator=(Matrix& other)
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


SqareMatrix::SqareMatrix() : Matrix(DIMENSION, DIMENSION){}

SqareMatrix::SqareMatrix(int n) : Matrix(n, n) {}

number SqareMatrix::calculateDetermenant() {

    number determenant = number(1, 1);
    SqareMatrix mat = SqareMatrix(dimension);

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
             mat.inputValue((*this)(i, j), i, j);;
        }
    }
    for (int i = 0; i < dimension; i++) {
        int pivot = i;

        for (int j = i + 1; j < dimension; j++) {
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

        for (int j = i + 1; j < dimension; j++) {
            number fact = mat(j, i) / mat(i, i);
            for (int k = i + 1; k < dimension; k++) {
                mat.inputValue(mat(j, k) - fact * mat(i, k), j, k);
            }
        }
    }
    return determenant;
}




int SqareMatrix::getDimension() {
    return dimension;
}

