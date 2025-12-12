#include "matrix.h"
#include <cstring> // memcpy


//  Konstruktor domyślny

matrix::matrix() : n(0), data(nullptr) {}



//  Konstruktor: alokuje n×n

matrix::matrix(int n) : n(n) {
    data = std::make_unique<int[]>(n * n);
    std::memset(data.get(), 0, n * n * sizeof(int)); // wypełnij zerami
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
    // unique_ptr zwalnia pamięć automatycznie
}



//  Funkcja alokacji pamięci

matrix& matrix::alokuj(int new_n) {
    // Jeśli nie ma pamięci → alokuj
    if (!data) {
        n = new_n;
        data = std::make_unique<int[]>(n * n);
        return *this;
    }

    // Jeśli pamięci jest za mało → alokuj od nowa
    if (new_n > n) {
        n = new_n;
        data = std::make_unique<int[]>(n * n);
        return *this;
    }

    // Jeśli pamięci jest więcej → nic nie rób
    // (czyli zostaw dotychczasową alokację)

    n = new_n;
    return *this;
}
