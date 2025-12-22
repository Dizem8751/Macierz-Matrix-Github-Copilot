/**
 * @file main.cpp
 * @brief Program testujący klasę matrix.
 * 
 * Ten program demonstruje różne operacje na macierzach kwadratowych:
 * - inicjalizacja i alokacja pamięci,
 * - algorytmy wypełniania (diagonalna, szachownica),
 * - operacje arytmetyczne (dodawanie, mnożenie),
 * - operatory porównania i modyfikujące.
 */

#include "matrix.h"
#include <iostream>

using namespace std;

/**
 * @brief Funkcja główna programu.
 * 
 * Wykonuje serię testów weryfikujących poprawność działania klasy matrix,
 * obejmujących:
 * - Test 1: Alokacja macierzy i losowanie wartości
 * - Test 2: Wypełnianie diagonali przesuniętej
 * - Test 3: Tworzenie wzoru szachownicy
 * - Test 4: Operacje arytmetyczne (dodawanie i mnożenie macierzy)
 * - Test 5: Użycie operatora() do dodania liczby zmiennoprzecinkowej
 * - Test 6: Realokacja i transponowanie dużej macierzy
 * - Test 7: Operatory porównania
 * 
 * @return int Kod powrotu (0 w przypadku pomyślnego wykonania).
 */
int main() {
     srand(time(NULL));

    std::cout << "--- Test 1: Alokacja i losowanie (n=5) ---" << std::endl;
    matrix A(5);
    A.losuj();
    std::cout << A << std::endl;

    std::cout << "--- Test 2: Diagonalna z przesunieciem (n=5, k=1) ---" << std::endl;
    int dane[] = {1, 1, 1, 1, 1};
    A.diagonalna_k(1, dane);
    std::cout << A << std::endl;

    std::cout << "--- Test 3: Szachownica (n=4) ---" << std::endl;
    matrix B(4);
    B.szachownica();
    std::cout << B << std::endl;

     std::cout << "--- Test 4: Operatory arytmetyczne ---" << std::endl;
    matrix C(3); C.losuj();
    matrix D(3); D.losuj();
    std::cout << "C:\n" << C << "D:\n" << D;
    
    matrix E = C + D;
    std::cout << "C + D:\n" << E << std::endl;
    
    matrix F = C * D;
    std::cout << "C * D:\n" << F << std::endl;

    std::cout << "--- Test 5: Operator() (double) ---" << std::endl;
    C(5.99); // Powinno dodac 5
    std::cout << "C + 5:\n" << C << std::endl;

     std::cout << "--- Test 6: Duza macierz (n=30) i realokacja ---" << std::endl;
    matrix G(2);
    G.alokuj(30); // Realokacja z 2 na 30
    G.losuj();
    // Nie wypisujemy, ale sprawdzamy czy program sie nie wysypie
    G.dowroc();
    std::cout << "Operacja odwrocenia na 30x30 zakonczona." << std::endl;

    // Test operatorów porównania
    matrix H(2), I(2);
    int tH[] = {1, 2, 3, 4};
    int tI[] = {1, 2, 3, 4};
    matrix tempH(2, tH);
    matrix tempI(2, tI);
    
    if (tempH == tempI) std::cout << "Macierze sa rowne.\n";
    else std::cout << "Macierze sa rozne.\n";

    return 0;
}
