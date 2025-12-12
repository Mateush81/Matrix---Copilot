#ifndef MATRIX_H
#define MATRIX_H

#include <memory>

class matrix {
private:
    int n;                                    // wymiar macierzy
    std::unique_ptr<int[]> data;              // wskaŸnik na dynamiczn¹ tablicê n*n

public:
    matrix();                                 // konstruktor domyœlny
    matrix(int n);                            // konstruktor z alokacj¹
    matrix(int n, int* t);                    // konstruktor z danymi
    matrix(matrix& m);                        // konstruktor kopiuj¹cy
    ~matrix();                                // destruktor

    matrix& alokuj(int n);                    // metoda alokacji pamiêci

    // pomocnicze funkcje dostêpu
    inline int& at(int x, int y) { return data[x * n + y]; }
};


