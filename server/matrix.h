#ifndef MATRIX_H
#define MATRIX_H

#include"number.h"

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

#endif // MATRIX_H
