#include "matrix.h"
#include <cstring>


//  Konstruktor domyślny

matrix::matrix() : n(0), data(nullptr) {}



//  Konstruktor: alokuje n×n

matrix::matrix(int n) : n(n) {
    data = std::make_unique<int[]>(n * n);
    std::memset(data.get(), 0, n * n * sizeof(int));
}



//  Konstruktor: alokuje n×n i kopiuje tablicę t

matrix::matrix(int n, int* t) : n(n) {
    data = std::make_unique<int[]>(n * n);
    std::memcpy(data.get(), t, n * n * sizeof(int));
}



//  Konstruktor kopiujący

matrix::matrix(matrix& m) : n(m.n) {
    if (m.data) {
        data = std::make_unique<int[]>(n * n);
        std::memcpy(data.get(), m.data.get(), n * n * sizeof(int));
    }
    else {
        data = nullptr;
    }
}



//  Destruktor

matrix::~matrix() {
    // unique_ptr automatycznie zwalnia pamięć
}



//  Metoda alokuj

matrix& matrix::alokuj(int new_n) {
    if (!data) {
        n = new_n;
        data = std::make_unique<int[]>(n * n);
        return *this;
    }

    if (new_n > n) {
        n = new_n;
        data = std::make_unique<int[]>(n * n);
        return *this;
    }

    n = new_n; // jeśli pamięci jest więcej, zostawiamy istniejącą
    return *this;
}



//  Wstawianie wartości

matrix& matrix::wstaw(int x, int y, int wartosc) {
    if (x >= 0 && x < n && y >= 0 && y < n) {
        data[x * n + y] = wartosc;
    }
    return *this;
}


//  Pokazanie wartości

int matrix::pokaz(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < n) {
        return data[x * n + y];
    }
    return 0;
}
