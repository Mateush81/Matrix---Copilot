#include <iostream>
#include <fstream>
#include "matrix.h"

using namespace std;

int main() {
    cout << "Tworzenie macierzy A (domyœlny konstruktor)...\n";
    matrix A;
    cout << "Macierz A utworzona (bez alokacji).\n\n";

    cout << "Tworzenie macierzy B o wymiarach 3x3...\n";
    matrix B(3);
    cout << "Macierz B utworzona.\n\n";

    cout << "Tworzenie macierzy C z danymi z tablicy...\n";
    int tablica[9] = { 1,2,3,4,5,6,7,8,9 };
    matrix C(3, tablica);
    cout << "Macierz C utworzona i wype³niona.\n\n";

    cout << "Kopiowanie macierzy C do macierzy D...\n";
    matrix D(C);
    cout << "Macierz D utworzona jako kopia macierzy C.\n\n";

    cout << "Alokacja macierzy A na wymiar 5x5...\n";
    A.alokuj(5);
    A.wstaw(0, 0, 10).wstaw(4, 4, 20);
    cout << "Macierz A wype³niona wybranymi wartoœciami.\n";
    cout << "A(0,0) = " << A.pokaz(0, 0) << ", A(4,4) = " << A.pokaz(4, 4) << "\n\n";

    cout << "Wczytywanie macierzy E o wymiarach 30x30 z pliku matrix30.txt...\n";
    matrix E(30);
    std::ifstream plik("matrix30.txt");
    if (!plik.is_open()) {
        cerr << "Nie mo¿na otworzyæ pliku matrix30.txt!\n";
        return 1;
    }
    for (int i = 0; i < 30; i++)
        for (int j = 0; j < 30; j++) {
            int x;
            plik >> x;
            E.wstaw(i, j, x);
        }
    plik.close();
    cout << "Macierz E wczytana.\n\n";

    cout << "Losowanie 10 elementów w macierzy E i transpozycja...\n";
    E.losuj(10);
    E.dowroc();
    cout << "Po losowaniu i transpozycji: E(0,0) = " << E.pokaz(0, 0)
        << ", E(29,29) = " << E.pokaz(29, 29) << "\n\n";

    cout << "Program zakoñczy³ dzia³anie.\n";
    return 0;
}
