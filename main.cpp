#include <iostream>
#include <fstream> // ifstream – wczytywanie danych z pliku
#include <cstdlib> // rand, srand – losowanie liczb
#include <ctime> // time() - generowanie liczb losowych
#include "matrix.h" // klasa matrix

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // KONSTRUKCJA I DESTRUKCJA OBIEKTÓW [4.1]
    cout << "=== Konstruktory i destruktor ===\n";

    matrix A;   // pusta, n = 0 
    matrix B(3);    // macierz 3×3 wype³niona zerami

    int tab[9] = { 1,2,3,4,5,6,7,8,9 };
    matrix C(3, tab);   // macierz 3×3 z danymi z tablicy tab
    matrix D(C);    // kopia macierzy C

    cout << "Macierz B (3x3 z zerami):\n" << B << "\n";
    cout << "Macierz C (z tablicy 1..9):\n" << C << "\n";
    cout << "Macierz D (kopia macierzy C):\n" << D << "\n";


    A.alokuj(5);                         // alokacja macierzy 5×5
    A.wstaw(0, 0, 10).wstaw(4, 4, 20);  // wstawienie wartoœci 10 i 20

    cout << "Macierz A po alokacji 5x5 i wstawieniu 10 i 20:\n" << A << "\n";


    // METODY MODYFIKACJI I ODCZYTU [4.2]
    cout << "=== Podstawowe metody modyfikacji i odczytu ===\n";

    matrix E(30);   // macierz 30×30
    ifstream plik("matrix30.txt");

    if (plik.is_open()) {
        cout << "Odczyt danych z pliku matrix30.txt\n";
        for (int i = 0; i < 30; i++)
            for (int j = 0; j < 30; j++) {
                int x;
                plik >> x;
                E.wstaw(i, j, x);
            }
        plik.close();
    }
    else {
        cout << "Nie mo¿na otworzyæ pliku matrix30.txt, wype³niam losowo\n";
        E.losuj();
    }

    cout << "Losowe wstawienie 10 elementów macierzy E:\n";
    E.losuj(10);

    cout << "Transpozycja macierzy E(dowroc)...\n";
    E.dowroc();


    cout << "Macierz E po trabspozycji:\n" << E << "\n";

    // fragment macierzy E
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << E.pokaz(i, j) << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    // METODY DIAGONALNE, WIERSZE I KOLUMNY [4.3]

    cout << "=== Metody diagonalne, wiersze i kolumny ===\n";

    matrix F(5);

    int t_diag[5] = { 1,2,3,4,5 };
    int t_diag2[5] = { 5,4,3,2,1 };
    int col[5] = { 9,8,7,6,5 };
    int row[5] = { 1,3,5,7,9 };


    cout << "\n-- diagonalna(t) --\n";
    F.diagonalna(t_diag);
    cout << F << "\n";

    cout << "-- diagonalna_k(1, t2) -- (przek¹tna przesuniêta o +1)\n";
    F.diagonalna_k(1, t_diag2);
    cout << F << "\n";

    cout << "-- kolumna(2, col) --\n";
    F.kolumna(2, col);
    cout << F << "\n";

    cout << "-- wiersz(1, row) --\n";
    F.wiersz(1, row);
    cout << F << "\n";

    cout << "-- przekatna() --\n";
    F.przekatna();
    cout << F << "\n";

    cout << "-- pod_przekatna() --\n";
    F.pod_przekatna();
    cout << F << "\n";

    cout << "-- nad_przekatna() --\n";
    F.nad_przekatna();
    cout << F << "\n";

    // TESTY 4.6
    cout << "=== Test operatorów 4.6 ===\n";
    F++;
    cout << "F++:\n" << F << "\n";

    F--;
    cout << "F--:\n" << F << "\n";

    F += 5;
    cout << "F += 5:\n" << F << "\n";

    F -= 2;
    cout << "F -= 2:\n" << F << "\n";

    F *= 3;
    cout << "F *= 3:\n" << F << "\n";

    F(4.7);
    cout << "F(4.7):\n" << F << "\n";

    // KONIEC
    return 0;
}
