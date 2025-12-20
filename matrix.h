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
    //--Konstruktory i destruktor--
    matrix();
    matrix(int n);
    matrix(int n, int* t);
    matrix(const matrix& m);
    ~matrix();
    matrix& alokuj(int n);

    matrix(int n, int* t);
    matrix(const matrix& m);
    ~matrix();

    // --Zarządzanie pamięcią--
    matrix& alokuj(int n);

    // --Operatory--
    matrix& wstaw(int x, int y, int wartosc);
    int pokaz(int x, int y) const;
    matrix& dowroc();
    matrix& losuj();
    matrix& losuj(int x);
};

#endif