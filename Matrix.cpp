#include "matrix.h"
#include <cstring>
#include <algorithm>
#include <cstdlib>

// 4.1 Konstrukcja
matrix::matrix() : n(0), data(nullptr) {}

matrix::matrix(int n) : n(n) {
    data = std::make_unique<int[]>(n * n);
    std::memset(data.get(), 0, n * n * sizeof(int));
}

matrix::matrix(int n, int* t) : n(n) {
    data = std::make_unique<int[]>(n * n);
    std::memcpy(data.get(), t, n * n * sizeof(int));
}

matrix::matrix(const matrix& m) : n(m.n) {
    if (m.data) {
        data = std::make_unique<int[]>(n * n);
        std::memcpy(data.get(), m.data.get(), n * n * sizeof(int));
    }
}

matrix::~matrix() {}

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

// 4.2 Modyfikacja
matrix& matrix::wstaw(int x, int y, int wartosc) {
    if (x >= 0 && x < n && y >= 0 && y < n)
        data[x * n + y] = wartosc;
    return *this;
}

int matrix::pokaz(int x, int y) const {
    if (x >= 0 && x < n && y >= 0 && y < n)
        return data[x * n + y];
    return 0;
}

matrix& matrix::dowroc() {
    auto tmp = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            tmp[j * n + i] = data[i * n + j];
    data = std::move(tmp);
    return *this;
}

matrix& matrix::losuj() {
    for (int i = 0; i < n * n; i++)
        data[i] = std::rand() % 10;
    return *this;
}

matrix& matrix::losuj(int x) {
    for (int i = 0; i < x; i++) {
        int r = std::rand() % (n * n);
        data[r] = std::rand() % 10;
    }
    return *this;
}

// 4.3 Przekątne
matrix& matrix::diagonalna(int* t) {
    std::fill(data.get(), data.get() + n * n, 0);
    for (int i = 0; i < n; i++)
        data[i * n + i] = t[i];
    return *this;
}

matrix& matrix::diagonalna_k(int k, int* t) {
    std::fill(data.get(), data.get() + n * n, 0);
    for (int i = 0; i < n; i++) {
        int j = i + k;
        if (j >= 0 && j < n)
            data[i * n + j] = t[i];
    }
    return *this;
}

matrix& matrix::kolumna(int x, int* t) {
    for (int i = 0; i < n; i++)
        data[i * n + x] = t[i];
    return *this;
}

matrix& matrix::wiersz(int y, int* t) {
    for (int j = 0; j < n; j++)
        data[y * n + j] = t[j];
    return *this;
}

matrix& matrix::przekatna() {
    std::fill(data.get(), data.get() + n * n, 0);
    for (int i = 0; i < n; i++)
        data[i * n + i] = 1;
    return *this;
}

matrix& matrix::pod_przekatna() {
    std::fill(data.get(), data.get() + n * n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            data[i * n + j] = 1;
    return *this;
}

matrix& matrix::nad_przekatna() {
    std::fill(data.get(), data.get() + n * n, 0);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            data[i * n + j] = 1;
    return *this;
}

// 4.4 Szachownica
matrix& matrix::szachownica() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            data[i * n + j] = (i + j) % 2;
    return *this;
}



// 4.5 Operatory arytmetyczne

matrix& matrix::operator+(matrix& m) {
    if (n != m.n || !data || !m.data) return *this;

    auto wynik = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n * n; i++)
        wynik[i] = data[i] + m.data[i];

    data = std::move(wynik);
    return *this;
}

matrix& matrix::operator*(matrix& m) {
    if (n != m.n || !data || !m.data) return *this;

    auto wynik = std::make_unique<int[]>(n * n);
    std::memset(wynik.get(), 0, n * n * sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                wynik[i * n + j] += data[i * n + k] * m.data[k * n + j];

    data = std::move(wynik);
    return *this;
}

matrix& matrix::operator+(int a) {
    if (!data) return *this;
    for (int i = 0; i < n * n; i++)
        data[i] += a;
    return *this;
}

matrix& matrix::operator*(int a) {
    if (!data) return *this;
    for (int i = 0; i < n * n; i++)
        data[i] *= a;
    return *this;
}

matrix& matrix::operator-(int a) {
    if (!data) return *this;
    for (int i = 0; i < n * n; i++)
        data[i] -= a;
    return *this;
}






// Operatory globalne (friend)

matrix operator+(int a, matrix& m) {
    matrix tmp(m);
    tmp + a;
    return tmp;
}

matrix operator*(int a, matrix& m) {
    matrix tmp(m);
    tmp* a;
    return tmp;
}

matrix operator-(int a, matrix& m) {
    matrix tmp(m);
    tmp - a;
    return tmp;
}








// Wypisywanie
std::ostream& operator<<(std::ostream& o, const matrix& m) {
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++)
            o << m.data[i * m.n + j] << " ";
        o << "\n";
    }
    return o;
}
