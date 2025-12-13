#include "matrix.h"      // Deklaracja klasy matrix i operatorów
#include <cstring>        // memcpy, memset – kopiowanie i zerowanie pamięci
#include <algorithm>      // std::fill – wypełnianie tablic
#include <cstdlib>        // rand() – generowanie losowych liczb

// ===== 4.1 Konstrukcja =====

// Konstruktor domyślny – tworzy pustą macierz (n = 0, brak danych)
matrix::matrix() : n(0), data(nullptr) {}

// Konstruktor z wymiarem n – alokuje pamięć dla macierzy n×n i wypełnia zerami
matrix::matrix(int n) : n(n) {
    data = std::make_unique<int[]>(n * n);  // alokacja pamięci dynamicznej
    std::memset(data.get(), 0, n * n * sizeof(int)); // zerowanie wszystkich elementów
}

// Konstruktor inicjalizujący macierz danymi z tablicy t
matrix::matrix(int n, int* t) : n(n) {
    data = std::make_unique<int[]>(n * n);   // alokacja pamięci
    std::memcpy(data.get(), t, n * n * sizeof(int)); // kopiowanie danych z tablicy t
}

// Konstruktor kopiujący – tworzy głęboką kopię istniejącej macierzy
matrix::matrix(const matrix& m) : n(m.n) {
    if (m.data) {
        data = std::make_unique<int[]>(n * n); // alokacja nowej pamięci
        std::memcpy(data.get(), m.data.get(), n * n * sizeof(int)); // kopiowanie danych
    }
}

// Destruktor – pamięć zwalniana automatycznie dzięki unique_ptr
matrix::~matrix() {}

// Alokacja nowej macierzy n×n i wyzerowanie jej zawartości
matrix& matrix::alokuj(int new_n) {
    n = new_n;
    data = std::make_unique<int[]>(n * n); // przydzielenie pamięci
    std::memset(data.get(), 0, n * n * sizeof(int)); // zerowanie
    return *this;
}

// ===== 4.2 Modyfikacja i dostęp =====

// Wstawienie wartości do konkretnej komórki (x, y)
matrix& matrix::wstaw(int x, int y, int wartosc) {
    if (x >= 0 && x < n && y >= 0 && y < n)
        data[x * n + y] = wartosc; // zapis wartości w odpowiednim indeksie
    return *this;
}

// Odczyt wartości z komórki (x, y)
int matrix::pokaz(int x, int y) const {
    if (x >= 0 && x < n && y >= 0 && y < n)
        return data[x * n + y]; // zwraca wartość
    return 0; // jeśli indeksy poza zakresem, zwraca 0
}

// Transpozycja macierzy – zamiana wierszy z kolumnami
matrix& matrix::dowroc() {
    auto tmp = std::make_unique<int[]>(n * n); // tymczasowa macierz
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            tmp[j * n + i] = data[i * n + j]; // zamiana wierszy i kolumn
    data = std::move(tmp); // kopiowanie wyniku do głównej macierzy
    return *this;
}

// Wypełnienie całej macierzy losowymi liczbami 0-9
matrix& matrix::losuj() {
    for (int i = 0; i < n * n; i++)
        data[i] = std::rand() % 10;
    return *this;
}

// Losowe wstawienie x wartości w losowe miejsca macierzy
matrix& matrix::losuj(int x) {
    for (int i = 0; i < x; i++)
        data[std::rand() % (n * n)] = std::rand() % 10;
    return *this;
}

// ===== 4.3 Przekątne, wiersze i kolumny =====

// Wypełnienie głównej przekątnej danymi z tablicy t
matrix& matrix::diagonalna(int* t) {
    std::fill(data.get(), data.get() + n * n, 0); // zerowanie całej macierzy
    for (int i = 0; i < n; i++)
        data[i * n + i] = t[i]; // wypełnianie głównej przekątnej
    return *this;
}

// Wypełnienie przesuniętej przekątnej o k pozycji
matrix& matrix::diagonalna_k(int k, int* t) {
    std::fill(data.get(), data.get() + n * n, 0); // zerowanie
    for (int i = 0; i < n; i++) {
        int j = i + k; // obliczenie przesuniętej kolumny
        if (j >= 0 && j < n)
            data[i * n + j] = t[i]; // wypełnianie elementów przesuniętej przekątnej
    }
    return *this;
}

// Wypełnienie wybranej kolumny danymi z tablicy t
matrix& matrix::kolumna(int x, int* t) {
    for (int i = 0; i < n; i++)
        data[i * n + x] = t[i];
    return *this;
}

// Wypełnienie wybranego wiersza danymi z tablicy t
matrix& matrix::wiersz(int y, int* t) {
    for (int j = 0; j < n; j++)
        data[y * n + j] = t[j];
    return *this;
}

// ===== 4.4 Wzory specjalne =====

// Wypełnienie głównej przekątnej jedynkami, reszta zer
matrix& matrix::przekatna() {
    std::fill(data.get(), data.get() + n * n, 0);
    for (int i = 0; i < n; i++)
        data[i * n + i] = 1;
    return *this;
}

// Wypełnienie elementów poniżej i na przekątnej jedynkami
matrix& matrix::pod_przekatna() {
    std::fill(data.get(), data.get() + n * n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            data[i * n + j] = 1;
    return *this;
}

// Wypełnienie elementów powyżej przekątnej jedynkami
matrix& matrix::nad_przekatna() {
    std::fill(data.get(), data.get() + n * n, 0);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            data[i * n + j] = 1;
    return *this;
}

// Wzór szachownicy – naprzemienne 0 i 1
matrix& matrix::szachownica() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            data[i * n + j] = (i + j) % 2;
    return *this;
}

// ===== 4.5 Operatory arytmetyczne =====

// Dodawanie macierzy
matrix& matrix::operator+(matrix& m) {
    for (int i = 0; i < n * n; i++)
        data[i] += m.data[i]; // każdy element sumowany
    return *this;
}

// Mnożenie macierzy – klasyczne mnożenie macierzy kwadratowych
matrix& matrix::operator*(matrix& m) {
    auto wynik = std::make_unique<int[]>(n * n); // tymczasowa macierz
    std::memset(wynik.get(), 0, n * n * sizeof(int)); // zerowanie
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                wynik[i * n + j] += data[i * n + k] * m.data[k * n + j]; // klasyczne mnożenie
    data = std::move(wynik);
    return *this;
}

// Operatory dodawania, odejmowania i mnożenia z liczbą całkowitą
matrix& matrix::operator+(int a) { for (int i = 0; i < n * n; i++) data[i] += a; return *this; }
matrix& matrix::operator-(int a) { for (int i = 0; i < n * n; i++) data[i] -= a; return *this; }
matrix& matrix::operator*(int a) { for (int i = 0; i < n * n; i++) data[i] *= a; return *this; }

// Operatory globalne dla liczb po lewej stronie
matrix operator+(int a, const matrix& m) { matrix tmp(m); tmp + a; return tmp; }
matrix operator-(int a, const matrix& m) { matrix tmp(m); tmp - a; return tmp; }
matrix operator*(int a, const matrix& m) { matrix tmp(m); tmp* a; return tmp; }

// ===== 4.6 Operatory inkrementacji/dekrementacji =====

// Inkrementacja wszystkich elementów o 1
matrix& matrix::operator++(int) { for (int i = 0; i < n * n; i++) data[i]++; return *this; }

// Dekrementacja wszystkich elementów o 1
matrix& matrix::operator--(int) { for (int i = 0; i < n * n; i++) data[i]--; return *this; }

// Przypisanie z działaniem dla liczby całkowitej
matrix& matrix::operator+=(int a) { return (*this + a); }
matrix& matrix::operator-=(int a) { return (*this - a); }
matrix& matrix::operator*=(int a) { return (*this * a); }

// Funkcja operatorowa () – dodaje część całkowitą liczby double do wszystkich elementów
matrix& matrix::operator()(double x) { int a = int(x); for (int i = 0; i < n * n; i++) data[i] += a; return *this; }

// ===== 4.7 Operatory strumieniowe i porównania =====

// Porównanie równości macierzy – wszystkie elementy muszą być równe
bool matrix::operator==(const matrix& m) const {
    if (n != m.n) return false; // różne wymiary → różne
    for (int i = 0; i < n * n; i++)
        if (data[i] != m.data[i])
            return false;
    return true;
}

// Operator "większości" – więcej niż połowa elementów większa od drugiej macierzy
bool matrix::operator>(const matrix& m) const {
    int count = 0;
    for (int i = 0; i < n * n; i++)
        if (data[i] > m.data[i])
            count++;
    return count >= (n * n / 2);
}

// Operator "mniejszości" – więcej niż połowa elementów mniejszych od drugiej macierzy
bool matrix::operator<(const matrix& m) const {
    int count = 0;
    for (int i = 0; i < n * n; i++)
        if (data[i] < m.data[i])
            count++;
    return count >= (n * n / 2);
}

// Operator wypisywania do strumienia (np. std::cout) – każda linia odpowiada wierszowi macierzy
std::ostream& operator<<(std::ostream& o, const matrix& m) {
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++)
            o << m.data[i * m.n + j] << " "; // wypisanie wartości elementu
        o << "\n"; // nowy wiersz
    }
    return o;
}
