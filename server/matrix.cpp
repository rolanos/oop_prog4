#include"matrix.h"
#include <cmath>

#define DIMENSION 4
#define INITIAL_VALUE 0.0

Matrix& Matrix::operator=(const Matrix& other)
{
    if (other.dimension == this->dimension)
    {
        for (int i = 0; i < dimension; i++)
        {
            for (int j = 0; j < dimension; j++)
            {
                this->matrix[i][j] = other.matrix[i][j];
            }
        }
    }

    return *this;
}

number& Matrix::operator() (const int i, const int j) {
    return matrix[i][j];
}

Matrix::Matrix(){
    dimension = DIMENSION;
    createMatrixWithDimension(dimension);
}

Matrix::Matrix(int n) {
    dimension = n;
    createMatrixWithDimension(dimension);
}

Matrix::~Matrix() {

    for (int i = 0; i < dimension; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}

void Matrix::inputValue(number value, int row, int column) {
    matrix[row][column] = value;
}

number Matrix::calculateDetermenant() {
    number determenant = number(1, 1);
    Matrix mat = Matrix(dimension);

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            mat.matrix[i][j] = this->matrix[i][j];
        }
    }
    for (int i = 0; i < dimension; i++) {
        int pivot = i;

        for (int j = i + 1; j < dimension; j++) {
            if (abs(mat.matrix[j][i]) > abs(mat.matrix[pivot][i])) {
                pivot = j;
            }
        }
        if (pivot != i) {
            swap(mat.matrix[i], mat.matrix[pivot]);
            determenant = determenant * (-1);
        }

        if (mat.matrix[i][i] == 0.0) {
            return number();
        }
        determenant = determenant * mat.matrix[i][i];

        for (int j = i + 1; j < dimension; j++) {
            number fact = mat.matrix[j][i] / mat.matrix[i][i];
            for (int k = i + 1; k < dimension; k++) {
                mat.matrix[j][k] = mat.matrix[j][k] - fact * mat.matrix[i][k];
            }
        }
    }
    return determenant;
}

Matrix& Matrix::calculateTranspose() {
    Matrix* transpose = new Matrix(dimension);
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            transpose->matrix[i][j] = matrix[j][i];
        }
    }
    return *transpose;
}

int Matrix::getRank() {
    int rank = dimension;
    Matrix mat = Matrix(dimension);

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            mat.matrix[i][j] = this->matrix[i][j];
        }
    }

    for (int row = 0; row < rank; row++)
    {
        if (mat.matrix[row][row])
        {
            for (int column = 0; column < mat.dimension; column++)
            {
                if (column != row)
                {

                    number mult = mat.matrix[column][row] /
                                  mat.matrix[row][row];
                    for (int i = 0; i < rank; i++)
                        mat.matrix[column][i] = mat.matrix[column][i] - mult * mat.matrix[row][i];
                }
            }
        }
        else
        {
            bool cut = true;
            for (int i = row + 1; i < mat.dimension; i++)
            {
                if (mat.matrix[i][row])
                {
                    for (int j = 0; j < rank; j++)
                    {
                        number temp = mat.matrix[row][i];
                        mat.matrix[row][j] = mat.matrix[i][j];
                        mat.matrix[i][j] = temp;
                    }

                    cut = false;
                    break;
                }
            }
            if (cut)
            {
                rank--;
                for (int i = 0; i < mat.dimension; i++)
                    mat.matrix[i][row] = mat.matrix[i][rank];
            }

            row--;
        }
    }
    return rank;
}



int Matrix::getDimension() {
    return dimension;
}

void Matrix::createMatrixWithDimension(int n) {
    matrix = new number*[n];

    for (int i = 0; i < n; i++)
    {
        matrix[i] = new number[n];
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = number();
        }
    }
}
