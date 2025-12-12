#include <iostream>
#include "matrix.h"

using namespace std;

int main() {

    cout << " Konstruktor domyœlny \n";
    matrix A;
    cout << "Utworzono macierz A (bez alokacji)\n\n";


    cout << " matrix(int n)\n";
    matrix B(3);   // 3x3
    cout << "Utworzono macierz B o wymiarach 3x3\n\n";


    cout << "matrix(int n, int* t) \n";
    int tablica[9] = {
        1,2,3,
        4,5,6,
        7,8,9
    };
    matrix C(3, tablica);
    cout << "Utworzono macierz C i przepisano dane z tablicy\n\n";


    cout << " Konstruktor kopiuj¹cy\n";
    matrix D(C);
    cout << "Utworzono macierz D jako kopiê macierzy C\n\n";


    cout << " alokuj(int n)\n";
    cout << "Alokujê macierz A na wymiar 5x5...\n";
    A.alokuj(5);
    cout << "Gotowe.\n\n";


    cout << "wstaw i pokaz \n";
    A.wstaw(0, 0, 10).wstaw(4, 4, 20);
    cout << "A(0,0) = " << A.pokaz(0, 0) << "\n";
    cout << "A(4,4) = " << A.pokaz(4, 4) << "\n\n";

    cout << " KONIEC \n";
    return 0;
}