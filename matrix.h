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

    // ==Algorytmy wypełniania macierzy==
    matrix& diagonalna(int* t);
    matrix& diagonalna_k(int k, int* t);
    matrix& kolumna(int x, int* t);
    matrix& wiersz(int y, int* t);
    matrix& przekatna();
    matrix& pod_przekatna();
    matrix& nad_przekatna();
    matrix& szachownica();

    // --Operatory Arytmetyczne--
    matrix& operator+(const matrix& m);
    matrix& operator*(const matrix& m);
    matrix& operator+(int a);
    matrix& operator*(int a);
    matrix& operator-(int a);
    
    // --Operatory modyfikujące--
    matrix& operator++(int);
    matrix& operator--(int);
    matrix& operator+=(int a);
    matrix& operator-=(int a);
    matrix& operator*=(int a);
    matrix& operator()(double d);

    // --Operator porównania--
    bool operator==(const matrix& m) const;
    bool operator>(const matrix& m) const;
    bool operator<(const matrix& m) const;
};


#endif