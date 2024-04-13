#include "matrix.h"

Matrix::Matrix() : Matrix::Matrix(0, 0) {}

Matrix::Matrix(int row, int column) {
    if(row == column) {
        dimension = row;
    }
    rowNumber = row;
    columnNumber = column;

    matrix = new number*[rowNumber];

    for (int i = 0; i < rowNumber; i++)
    {
        matrix[i] = new number[columnNumber];
        for (int j = 0; j < columnNumber; j++)
        {
            matrix[i][j] = number();
        }
    }
}

Matrix::~Matrix() {

    for (int i = 0; i < rowNumber; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}

number& Matrix::operator() (const int i, const int j) {
    return matrix[i][j];
}


void Matrix::inputValue(number value, int row, int column) {
    matrix[row][column] = value;
}

Matrix& Matrix::calculateTranspose() {
    Matrix* transpose = new Matrix(columnNumber, rowNumber);
    for (int i = 0; i < rowNumber; i++)
    {
        for (int j = 0; j < columnNumber; j++)
        {
            transpose->matrix[i][j] = matrix[j][i];
        }
    }
    return *transpose;
}

void Matrix::swapRows(int first, int second) {
    swap(matrix[first], matrix[second]);
}

bool Matrix::isSqare() {
    return rowNumber == columnNumber;
}

int Matrix::getRowNumber() {
    return rowNumber;
}

int Matrix::getColumnNumber() {
    return columnNumber;
}

int Matrix::getRank() {
    int rank = rowNumber;
    Matrix mat = Matrix(rowNumber, columnNumber);

    for (int i = 0; i < rowNumber; i++)
    {
        for (int j = 0; j < columnNumber; j++)
        {
            mat.matrix[i][j] = this->matrix[i][j];
        }
    }

    for (int row = 0; row < rank; row++)
    {
        if (mat.matrix[row][row])
        {
            for (int column = 0; column < mat.columnNumber; column++)
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
            for (int i = row + 1; i < mat.rowNumber; i++)
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
                //???
                for (int i = 0; i < mat.columnNumber; i++)
                    mat.matrix[i][row] = mat.matrix[i][rank];
            }

            row--;
        }
    }
    return rank;
}
