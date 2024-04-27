#include "complex.h"
#include <cmath>

TComplex::TComplex() {
    real = 0;
    imaginary = 0;
}

TComplex::TComplex(const double& r) {
    real = r;
    imaginary = 0;
}

TComplex::TComplex(double r, double i) {
    real = r;
    imaginary = i;
}


TComplex TComplex::operator*(TComplex complex)
{
    TComplex result;
    result.real = real * complex.real - imaginary * complex.imaginary;
    result.imaginary = real * complex.imaginary + imaginary * complex.real;
    return result;
}

TComplex TComplex::operator*(int lambda)
{
    TComplex result;
    result.real = lambda * real;
    result.imaginary = lambda * imaginary;
    return result;
}

TComplex TComplex::operator/(TComplex complex)
{
    TComplex result;
    result.real = (real * complex.real + imaginary * complex.imaginary) / (pow(complex.real, 2) + pow(complex.imaginary, 2));
    result.imaginary = (complex.real*imaginary - real * complex.imaginary) / (pow(complex.real, 2) + pow(complex.imaginary, 2));
    return result;
}

TComplex TComplex::operator+(const TComplex& complex)
{
    TComplex result;
    result.real = real + complex.real;
    result.imaginary = imaginary + complex.imaginary;
    return result;
}

TComplex TComplex::operator-(const TComplex& complex)
{
    TComplex result;
    result.real = real - complex.real;
    result.imaginary = imaginary - complex.imaginary;
    return result;
}

double TComplex::getReal() {
    return real;
}

double TComplex::getImaginary() {
    return imaginary;
}

bool TComplex::operator==(const int& r)
{
    if (r == 0 && real == 0 && imaginary == 0)
    {
        return true;
    }
    return false;
}

TComplex::operator bool() const
{
    if (real <= 0 && imaginary <= 0)
    {
        return false;
    }
    return true;
}



double abs(TComplex complex)
{
    return sqrt(pow(complex.real, 2) + pow(complex.imaginary, 2));
}

ostream& operator<<(ostream& output, TComplex& complex) {
    char betweenOperator = complex.imaginary >= 0 ? '+' : '\0';

    output << complex.real << betweenOperator << complex.imaginary;
    return output;
}

istream& operator>>(istream& input, TComplex& complex) {
    input >> complex.real >> complex.imaginary;
    return input;
}
