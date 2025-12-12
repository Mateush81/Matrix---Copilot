#include "matrix.h"
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

// Konstruktor domyślny
matrix::matrix() : n(0), data(nullptr) {}

// Konstruktor: alokuje n×n
matrix::matrix(int n) : n(n) {
    data = std::make_unique<int[]>(n * n);
    std::memset(data.get(), 0, n * n * sizeof(int));
}

// Konstruktor: alokuje n×n i kopiuje tablicę t
matrix::matrix(int n, int* t) : n(n) {
    data = std::make_unique<int[]>(n * n);
    std::memcpy(data.get(), t, n * n * sizeof(int));
}

// Konstruktor kopiujący
matrix::matrix(const matrix& m) : n(m.n) {
    if (m.data) {
        data = std::make_unique<int[]>(n * n);
        std::memcpy(data.get(), m.data.get(), n * n * sizeof(int));
    }
    else {
        data = nullptr;
    }
}

// Destruktor
matrix::~matrix() {}

// Metoda alokuj
matrix& matrix::alokuj(int new_n) {
    if (!data || new_n > n) {
        n = new_n;
        data = std::make_unique<int[]>(n * n);
        std::memset(data.get(), 0, n * n * sizeof(int));
    }
    else {
        n = new_n;
    }
    return *this;
}

// Wstawianie wartości
matrix& matrix::wstaw(int x, int y, int wartosc) {
    if (x >= 0 && x < n && y >= 0 && y < n)
        data[x * n + y] = wartosc;
    return *this;
}

// Pokazanie wartości
int matrix::pokaz(int x, int y) const {
    if (x >= 0 && x < n && y >= 0 && y < n)
        return data[x * n + y];
    return 0;
}

// Transpozycja macierzy
matrix& matrix::dowroc() {
    if (!data) return *this;
    auto nowa = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            nowa[j * n + i] = data[i * n + j];
    data = std::move(nowa);
    return *this;
}

// Wypełnienie całej macierzy losowymi cyframi 0-9
matrix& matrix::losuj() {
    if (!data) return *this;
    for (int i = 0; i < n * n; i++)
        data[i] = std::rand() % 10;
    return *this;
}

// Losowe wstawienie x cyfr w losowe miejsca
matrix& matrix::losuj(int x) {
    if (!data || x <= 0) return *this;
    for (int i = 0; i < x; i++) {
        int randX = std::rand() % n;
        int randY = std::rand() % n;
        int wart = std::rand() % 10;
        data[randX * n + randY] = wart;
    }
    return *this;
}

// Metody diagonalne
matrix& matrix::diagonalna(int* t) {
    if (!data) return *this;
    std::fill(data.get(), data.get() + n * n, 0);
    for (int i = 0; i < n; i++)
        data[i * n + i] = t[i];
    return *this;
}

matrix& matrix::diagonalna_k(int k, int* t) {
    if (!data) return *this;
    std::fill(data.get(), data.get() + n * n, 0);
    for (int i = 0; i < n; i++) {
        int j = i + k;
        if (j >= 0 && j < n)
            data[i * n + j] = t[i];
    }
    return *this;
}

// Kolumny i wiersze
matrix& matrix::kolumna(int x, int* t) {
    if (!data || x < 0 || x >= n) return *this;
    for (int i = 0; i < n; i++)
        data[i * n + x] = t[i];
    return *this;
}

matrix& matrix::wiersz(int y, int* t) {
    if (!data || y < 0 || y >= n) return *this;
    for (int j = 0; j < n; j++)
        data[y * n + j] = t[j];
    return *this;
}

// Wypełnienie przekątnych
matrix& matrix::przekatna() {
    if (!data) return *this;
    std::fill(data.get(), data.get() + n * n, 0);
    for (int i = 0; i < n; i++)
        data[i * n + i] = 1;
    return *this;
}

matrix& matrix::pod_przekatna() {
    if (!data) return *this;
    std::fill(data.get(), data.get() + n * n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            data[i * n + j] = 1;
    return *this;
}

matrix& matrix::nad_przekatna() {
    if (!data) return *this;
    std::fill(data.get(), data.get() + n * n, 0);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            data[i * n + j] = 1;
    return *this;
}

// Operator <<
std::ostream& operator<<(std::ostream& o, const matrix& m) {
    if (!m.rozmiar()) return o;
    for (int i = 0; i < m.rozmiar(); i++) {
        for (int j = 0; j < m.rozmiar(); j++)
            o << m.at(i, j) << " ";
        o << "\n";
    }
    return o;
}



matrix& matrix::szachownica() {
    if (!data) return *this;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            data[i * n + j] = (i + j) % 2;
    return *this;
}


matrix& matrix::operator+(matrix& m) {
    if (n != m.n || !data || !m.data) return *this;
    auto wynik = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n * n; i++)
        wynik[i] = data[i] + m.data[i];
    data = std::move(wynik);
    return *this;
}