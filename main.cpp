#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "matrix.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "=== Konstruktory i destruktor ===\n";

    matrix A;
    matrix B(3);
    int tab[9] = { 1,2,3,4,5,6,7,8,9 };
    matrix C(3, tab);
    matrix D(C);

    A.alokuj(5);
    A.wstaw(0, 0, 10).wstaw(4, 4, 20);
    cout << "Macierz A:\n" << A << "\n";

    cout << "=== Podstawowe metody modyfikacji i odczytu ===\n";
    matrix E(30);
    ifstream plik("matrix30.txt");
    if (plik.is_open()) {
        for (int i = 0; i < 30; i++)
            for (int j = 0; j < 30; j++) {
                int x;
                if (!(plik >> x)) x = 0;
                E.wstaw(i, j, x);
            }
        plik.close();
    }
    else {
        E.losuj();
    }

    E.losuj(10);
    E.dowroc();

    cout << "=== Metody diagonalne, wiersze i kolumny ===\n";
    matrix F(5);
    int t_diag[5] = { 1,2,3,4,5 };
    int t_diag2[5] = { 5,4,3,2,1 };
    int col[5] = { 9,8,7,6,5 };
    int row[5] = { 1,3,5,7,9 };

    F.diagonalna(t_diag);
    cout << F << "\n";
    F.diagonalna_k(1, t_diag2);
    cout << F << "\n";
    F.kolumna(2, col);
    cout << F << "\n";
    F.wiersz(1, row);
    cout << F << "\n";
    F.przekatna();
    cout << F << "\n";
    F.pod_przekatna();
    cout << F << "\n";
    F.nad_przekatna();
    cout << F << "\n";

    return 0;
}
