#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "matrix.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // KONSTRUKCJA I DESTRUKCJA OBIEKTÓW [4.1–4.2]
    matrix A(3);
    int tab[9] = { 1,2,3,4,5,6,7,8,9 };
    matrix B(3, tab);

    cout << "Macierz A:\n" << A << "\n";
    cout << "Macierz B:\n" << B << "\n";

    // ===== 4.3–4.4 =====
    matrix F(5);
    int t_diag[5] = { 1,2,3,4,5 };
    int col[5] = { 9,8,7,6,5 };
    F.diagonalna(t_diag);
    F.kolumna(2, col);
    F.szachownica();

    cout << "Macierz F po modyfikacjach:\n" << F << "\n";

    // ===== 4.6 =====
    F++; F--; F += 5; F -= 2; F *= 2; F(3.7);
    cout << "Macierz F po operatorach 4.6:\n" << F << "\n";

    // ===== 4.7 =====
    matrix G(5, t_diag);
    cout << "G == F? " << (G == F) << "\n";
    cout << "G > F? " << (G > F) << "\n";
    cout << "G < F? " << (G < F) << "\n";
    cout << "Wypisanie macierzy G:\n" << G << "\n";

    return 0;
}
