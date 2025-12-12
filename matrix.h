 #pragma once 





#include <memory>
#include <iostream>

class matrix {
private:
    int n;                                  // wymiar macierzy
    std::unique_ptr<int[]> data;            // wskaŸnik na dynamiczn¹ tablicê n*n

public:
    // KONSTRUKTORY I DESTRUKTOR
    matrix();                               // konstruktor domyœlny
    matrix(int n);                          // konstruktor z alokacj¹
    matrix(int n, int* t);                  // konstruktor z kopiowaniem danych
    matrix(matrix& m);                      // konstruktor kopiuj¹cy
    ~matrix();                              // destruktor

    // METODY
    matrix& alokuj(int n);                  // alokacja pamiêci (lub dopasowanie istniej¹cej)
    matrix& wstaw(int x, int y, int wartosc); // wstawienie wartoœci
    int pokaz(int x, int y);                 // pokazanie wartoœci w komórce

    // pomocnicza funkcja dostêpu
    inline int& at(int x, int y) { return data[x * n + y]; }
    inline int rozmiar() { return n; }
};

 

