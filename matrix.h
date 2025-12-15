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

};

#endif