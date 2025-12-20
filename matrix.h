#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <memory>
#include <iomanip>

class matrix {
private:
    std::unique_ptr<int[]> data; // Inteligentny wskaźnik do tablicy
    int n;                       // Aktualny rozmiar logiczny macierzy (n x n)
    int allocated_n;             // Rozmiar fizycznie zaalokowanej pamięci

public:
    // --- Konstruktory i Destruktor ---
    matrix();
    matrix(int n);
    matrix(int n, int* t);
    matrix(const matrix& m); // Konstruktor kopiujący (Głęboka kopia)
    ~matrix();

    // --- Zarządzanie pamięcią ---
    matrix& alokuj(int n);

    // --- Metody operacyjne ---
    matrix& wstaw(int x, int y, int wartosc);
    int pokaz(int x, int y) const;
    matrix& dowroc(); // Transpozycja
    matrix& losuj();
    matrix& losuj(int x); // Losuje x cyfr w losowe miejsca

    // --- Algorytmy wypełniania ---
    matrix& diagonalna(int* t);
    matrix& diagonalna_k(int k, int* t);
    matrix& kolumna(int x, int* t);
    matrix& wiersz(int y, int* t);
    matrix& przekatna();
    matrix& pod_przekatna();
    matrix& nad_przekatna();
    matrix& szachownica();

    // --- Operatory Arytmetyczne ---
    matrix operator+(const matrix& m);
    matrix operator*(const matrix& m);
    matrix operator+(int a);
    matrix operator*(int a);
    matrix operator-(int a);

    // --- Operatory Modyfikujące ---
    matrix& operator++(int); // Postinkrementacja
    matrix& operator--(int); // Postdekrementacja
    matrix& operator+=(int a);
    matrix& operator-=(int a);
    matrix& operator*=(int a);
    matrix& operator()(double val); // Dodanie części całkowitej

    // --- Operatory Porównania ---
    bool operator==(const matrix& m);
    bool operator>(const matrix& m);
    bool operator<(const matrix& m);

    // --- Funkcje Zaprzyjaźnione ---
    friend matrix operator+(int a, matrix& m);
    friend matrix operator*(int a, matrix& m);
    friend matrix operator-(int a, matrix& m);
    friend std::ostream& operator<<(std::ostream& o, matrix& m);
};

#endif