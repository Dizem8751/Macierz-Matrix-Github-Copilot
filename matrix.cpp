#include "matrix.h"

matrix::matrix() : n(0), allocated_n(0), data(nullptr) {}

matrix::matrix(int n) : n(0), allocated_n(0), data(nullptr) {
    alokuj(n);
}

matrix::~matrix() {}

matrix& matrix::alokuj(int req_n) {
    if (req_n <= 0) return *this;
    if (allocated_n < req_n) {
        data = std::make_unique<int[]>(req_n * req_n);
        allocated_n = req_n;
    }
    n = req_n;
    // Opcjonalne zerowanie
    if(allocated_n == req_n) { for(int i=0; i<n*n; ++i) data[i] = 0; }
    return *this;
    
}
matrix::matrix(int n, int* t) : matrix(n) {
    for (int i = 0; i < n * n; ++i) data[i] = t[i];
}

matrix::matrix(const matrix& m) : n(m.n), allocated_n(m.allocated_n) {
    if (m.data) {
        data = std::make_unique<int[]>(allocated_n * allocated_n);
        for (int i = 0; i < n * n; ++i) data[i] = m.data[i];
    }
}

matrix& matrix::wstaw(int x, int y, int wartosc) {
    if (x < 0 || x >= n || y < 0 || y >= n) return *this;
    data[y * n + x] = wartosc;
    return *this;
}

int matrix::pokaz(int x, int y) const {
    if (x < 0 || x >= n || y < 0 || y >= n) return 0;
    return data[y * n + x];
}

matrix& matrix::dowroc() {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            std::swap(data[i * n + j], data[j * n + i]);
        }
    }
    return *this;
}

matrix& matrix::losuj() {
    for (int i = 0; i < n * n; ++i) {
        data[i] = rand() % 10; // Losowe wartości od 0 do 9
    }
    return *this;
}

matrix& matrix::losuj(int x) {
    for (int i=0; i<n*n; ++i) data[i] = 0;
    for (int k=0; k<x; ++k ) {
        int r = rand() % n;
        int c = rand() % n;
        data[r*n + c] = rand() % 10;
    }
    return *this;
}

//-- Algorytmy wypełniania macierzy --//
matrix& matrix::diagonalna(int* t) {
    return diagonalna_k(0, t);
}

matrix& matrix::diagonalna_k(int k, int* t) {
    for (int i = 0; i <n * n; i++) data[i] = 0;

    int idx = 0;
    for (int i = 0; i < n; ++i) {
        int j = i + k;
        if (j >= 0 && j < n) {
            data[i * n + j] = t[idx++];
        }
    }
    return *this;
}

matrix& matrix::kolumna(int x, int* t) {
    if (x >= 0 && x < n) {
        for (int i = 0; i < n; ++i) data[i * n + x] = t[i];
    }
    return *this;
}

matrix& matrix::wiersz(int y, int* t) {
    if (y >= 0 && y < n) {
        for (int i = 0; i < n; ++i) data[y * n + i] = t[i];
    }
    return *this;
}

matrix& matrix::przekatna() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            data[i * n + j] = (i == j) ? 1 : 0;
    return *this;
}

matrix& matrix::pod_przekatna() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            data[i * n + j] = (i > j) ? 1 : 0;
    return *this;
}

matrix& matrix::nad_przekatna() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            data[i * n + j] = (i < j) ? 1 : 0;
    return *this;
}

matrix& matrix::szachownica() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            data[i * n + j] = ((i + j) % 2 == 0) ? 1 : 0;
    return *this;
}


