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
    matrix(const matrix& m);                // konstruktor kopiuj¹cy
    ~matrix();                              // destruktor

    // METODY
    matrix& alokuj(int n);                  // alokacja pamiêci
    matrix& wstaw(int x, int y, int wartosc); // wstawienie wartoœci
    int pokaz(int x, int y) const;          // pokazanie wartoœci w komórce

    // METODY MODYFIKACJI I DOSTÊPU
    matrix& dowroc(void);                   // transpozycja macierzy
    matrix& losuj(void);                    // wype³nienie ca³ej macierzy losowymi cyframi 0-9
    matrix& losuj(int x);                   // losowe wstawienie x cyfr w losowe miejsca

    // pomocnicza funkcja dostêpu
    inline int& at(int x, int y) { return data[x * n + y]; }
    inline int at(int x, int y) const { return data[x * n + y]; }
    inline int rozmiar() const { return n; }

    // Metody diagonalne 
    matrix& diagonalna(int* t);             // wype³nienie g³ównej przek¹tnej danymi z tablicy
    matrix& diagonalna_k(int k, int* t);     // przesuniêta przek¹tna 

    // Metody dla kolumn i wierszy
    matrix& kolumna(int x, int* t);         // wype³nienie kolumny
    matrix& wiersz(int y, int* t);          // wype³nienie wiersza

    // Metody binarne wype³niaj¹ce przek¹tn¹
    matrix& przekatna(void);                // 1 na przek¹tnej, 0 poza ni¹
    matrix& pod_przekatna(void);            // 1 pod przek¹tn¹ i na przek¹tnej, 0 nad
    matrix& nad_przekatna(void);            // 1 nad przek¹tn¹, 0 pod i na

    // Operator wypisywania
    friend std::ostream& operator<<(std::ostream& o, const matrix& m);
};

