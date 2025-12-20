#include "matrix.h"
#include <cstdlib>
#include <cmath>
#include <algorithm>

// --- Konstruktory ---
matrix::matrix() : n(0), allocated_n(0), data(nullptr) {}

matrix::matrix(int n) : n(0), allocated_n(0), data(nullptr) {
    alokuj(n);
}

matrix::matrix(int n, int* t) : matrix(n) {
    for (int i = 0; i < n * n; ++i) {
        data[i] = t[i];
    }
}

// Konstruktor kopiujący - musi wykonać głęboką kopię (deep copy)
matrix::matrix(const matrix& m) : n(m.n), allocated_n(m.allocated_n) {
    if (m.data) {
        data = std::make_unique<int[]>(allocated_n * allocated_n);
        for (int i = 0; i < n * n; ++i) {
            data[i] = m.data[i];
        }
    }
}

matrix::~matrix() {
    // unique_ptr zwalnia pamięć automatycznie
}

// --- Metoda Alokuj ---
matrix& matrix::alokuj(int req_n) {
    if (req_n <= 0) return *this;

    if (allocated_n < req_n) {
        // Jeśli mamy za mało pamięci, musimy przearanżować
        // unique_ptr automatycznie usunie starą tablicę przy przypisaniu nowej
        data = std::make_unique<int[]>(req_n * req_n);
        allocated_n = req_n;
    }
    // Jeśli allocated_n >= req_n, nie robimy nic (zostawiamy alokację),
    // tylko zmieniamy logiczny rozmiar n.
    n = req_n;
    
    // Opcjonalnie: zerowanie nowej pamięci dla bezpieczeństwa
    if(allocated_n == req_n) { 
        for(int i=0; i<n*n; ++i) data[i] = 0;
    }

    return *this;
}

// --- Metody Podstawowe ---
matrix& matrix::wstaw(int x, int y, int wartosc) {
    if (x >= 0 && x < n && y >= 0 && y < n) data[x * n + y] = wartosc;
    return *this;
}

int matrix::pokaz(int x, int y) const {
    if (x >= 0 && x < n && y >= 0 && y < n) return data[x * n + y];
    return 0;
}

matrix& matrix::dowroc() {
    auto temp = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            temp[j * n + i] = data[i * n + j];
        }
    }
    data = std::move(temp);
    return *this;
}

matrix& matrix::losuj() {
    for (int i = 0; i < n * n; ++i) data[i] = rand() % 10;
    return *this;
}

matrix& matrix::losuj(int x) {
    for (int i = 0; i < n * n; ++i) data[i] = 0; // Najpierw zerujemy
    for (int k = 0; k < x; ++k) {
        int r = rand() % n;
        int c = rand() % n;
        data[r * n + c] = rand() % 10;
    }
    return *this;
}

// --- Algorytmy ---
matrix& matrix::diagonalna(int* t) {
    return diagonalna_k(0, t);
}

matrix& matrix::diagonalna_k(int k, int* t) {
    for (int i = 0; i < n * n; ++i) data[i] = 0;
    
    int idx = 0;
    for (int i = 0; i < n; ++i) {
        int j = i + k; // Przesunięcie kolumny względem wiersza
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
            data[i * n + j] = (j > i) ? 1 : 0;
    return *this;
}

matrix& matrix::szachownica() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            data[i * n + j] = (i + j) % 2;
    return *this;
}

// --- Operatory ---
matrix matrix::operator+(const matrix& m) {
    matrix temp(n);
    if (n != m.n) return temp;
    for (int i = 0; i < n * n; ++i) temp.data[i] = data[i] + m.data[i];
    return temp;
}

matrix matrix::operator*(const matrix& m) {
    matrix temp(n);
    if (n != m.n) return temp;
    // Mnożenie macierzy
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int sum = 0;
            for (int k = 0; k < n; ++k) {
                sum += data[i * n + k] * m.data[k * n + j];
            }
            temp.data[i * n + j] = sum;
        }
    }
    return temp;
}

matrix matrix::operator+(int a) {
    matrix temp(*this);
    for (int i = 0; i < n * n; ++i) temp.data[i] += a;
    return temp;
}

matrix matrix::operator*(int a) {
    matrix temp(*this);
    for (int i = 0; i < n * n; ++i) temp.data[i] *= a;
    return temp;
}

matrix matrix::operator-(int a) {
    matrix temp(*this);
    for (int i = 0; i < n * n; ++i) temp.data[i] -= a;
    return temp;
}

matrix& matrix::operator++(int) {
    for (int i = 0; i < n * n; ++i) data[i]++;
    return *this;
}

matrix& matrix::operator--(int) {
    for (int i = 0; i < n * n; ++i) data[i]--;
    return *this;
}

matrix& matrix::operator+=(int a) {
    for (int i = 0; i < n * n; ++i) data[i] += a;
    return *this;
}

matrix& matrix::operator-=(int a) {
    for (int i = 0; i < n * n; ++i) data[i] -= a;
    return *this;
}

matrix& matrix::operator*=(int a) {
    for (int i = 0; i < n * n; ++i) data[i] *= a;
    return *this;
}

matrix& matrix::operator()(double val) {
    int intPart = static_cast<int>(val);
    for (int i = 0; i < n * n; ++i) data[i] += intPart;
    return *this;
}

bool matrix::operator==(const matrix& m) {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i)
        if (data[i] != m.data[i]) return false;
    return true;
}

bool matrix::operator>(const matrix& m) {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i)
        if (data[i] <= m.data[i]) return false; // Wystarczy jeden element <= aby całość nie była >
    return true;
}

bool matrix::operator<(const matrix& m) {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i)
        if (data[i] >= m.data[i]) return false;
    return true;
}

// --- Funkcje Zaprzyjaźnione ---
matrix operator+(int a, matrix& m) { return m + a; }
matrix operator*(int a, matrix& m) { return m * a; }
matrix operator-(int a, matrix& m) {
    matrix temp(m.n);
    for (int i = 0; i < m.n * m.n; ++i) temp.data[i] = a - m.data[i];
    return temp;
}

std::ostream& operator<<(std::ostream& o, matrix& m) {
    for (int i = 0; i < m.n; ++i) {
        o << "| ";
        for (int j = 0; j < m.n; ++j) {
            o << std::setw(3) << m.data[i * m.n + j] << " ";
        }
        o << "|\n";
    }
    return o;
}