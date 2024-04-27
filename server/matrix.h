#ifndef MATRIX_H
#define MATRIX_H


template <class number>
class Matrix
{
public:
    Matrix();
    Matrix(int, int);
    ~Matrix();

    //Ввод элементов в матрицу
    void inputValue(number, int, int);
    //Поменять местами строки
    void swapRows(int, int);
    //Получить ранг матрицы
    int getRank();
    //Проверка на квадратную матрицу
    bool isSqare();
    //Получить количество строк в матрице
    int getRowNumber();
    //Получить количество столбцов в матрице
    int getColumnNumber();
    //Получение транспонированной матрицы
    Matrix& calculateTranspose();

    //Выбор элемента матрицы
    number& operator() (const int i, const int j);
protected:
    //Размерность
    int dimension;
private:
    //matrix с модификатором доступа private, чтобы пользователь не мог напрямую изменять элементы, а делал это чере интерфейс inputValue(number, int, int)
    number** matrix;
    //rowNumber и columnNumber с модификатором доступа private, чтобы пользователь не мог напрямую менять размерность, что приведет к потере данных в ячейках матрицы
    //для инициализции количества строк и столбцов мы используем конструктор Matrix(int, int), а для получения getRowNumber() и getColumnNumber()
    int rowNumber;
    int columnNumber;
};

template <class number>
Matrix<number>::Matrix() : Matrix::Matrix(0, 0) {}

template <class number>
Matrix<number>::Matrix(int row, int column) {
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

template <class number>
Matrix<number>::~Matrix() {

    for (int i = 0; i < rowNumber; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}

template <class number>
number& Matrix<number>::operator() (const int i, const int j) {
    return matrix[i][j];
}

template <class number>
void Matrix<number>::inputValue(number value, int row, int column) {
    matrix[row][column] = value;
}

template <class number>
Matrix<number>& Matrix<number>::calculateTranspose() {
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
template <class number>
void Matrix<number>::swapRows(int first, int second) {
    for (int i = 0; i < columnNumber; i++) {
        number buffer = matrix[first][i];
        inputValue(matrix[second][i], first, i);
        inputValue(buffer, second, i);
    }
}
template <class number>
bool Matrix<number>::isSqare() {
    return rowNumber == columnNumber;
}
template <class number>
int Matrix<number>::getRowNumber() {
    return rowNumber;
}
template <class number>
int Matrix<number>::getColumnNumber() {
    return columnNumber;
}
template <class number>
int Matrix<number>::getRank() {
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
                    for (int i = 0; i < rank; i++) {
                        number a = mat.matrix[column][i];
                        number b = mat.matrix[row][i];
                        mat.matrix[column][i] = mat.matrix[column][i] - mult * mat.matrix[row][i];
                    }

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

#endif // MATRIX_H
