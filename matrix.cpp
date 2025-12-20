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