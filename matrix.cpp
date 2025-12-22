#include "matrix.h"
#include <cstdlib>
#include <cmath>
#include <algorithm>

// --- Konstruktory ---

/**
 * @brief Domyślny konstruktor. Inicjalizuje macierz o rozmiarze 0.
 */
matrix::matrix() : n(0), allocated_n(0), data(nullptr) {}

/**
 * @brief Konstruktor z parametrem rozmiaru. Alokuje pamięć dla macierzy n×n.
 * @param n Rozmiar macierzy (n x n). Jeśli n ≤ 0, macierz pozostaje pusta.
 */
matrix::matrix(int n) : n(0), allocated_n(0), data(nullptr) {
    alokuj(n);
}

/**
 * @brief Konstruktor inicjujący macierz wartościami z tablicy.
 * @param n Rozmiar macierzy (n x n).
 * @param t Wskaźnik na tablicę zawierającą n² elementów w porządku wiersz po wierszu.
 */
matrix::matrix(int n, int* t) : matrix(n) {
    for (int i = 0; i < n * n; ++i) {
        data[i] = t[i];
    }
}

/**
 * @brief Konstruktor kopiujący. Wykonuje głęboką kopię danych macierzy.
 * @param m Macierz do skopiowania.
 */
matrix::matrix(const matrix& m) : n(m.n), allocated_n(m.allocated_n) {
    if (m.data) {
        data = std::make_unique<int[]>(allocated_n * allocated_n);
        for (int i = 0; i < n * n; ++i) {
            data[i] = m.data[i];
        }
    }
}

/**
 * @brief Destruktor. Automatycznie zwalnia dynamicznie przydzieloną pamięć poprzez unique_ptr.
 */
matrix::~matrix() {
    // unique_ptr zwalnia pamięć automatycznie
}

// --- Metoda Alokuj ---

/**
 * @brief Alokuje lub realokuje pamięć dla macierzy o zadanym rozmiarze.
 * 
 * Jeśli żądana pamięć jest większa niż dotychczas przydzielona, dokonywana jest realokacja.
 * W przeciwnym razie zmienia się tylko rozmiar logiczny macierzy.
 * Nowa pamięć jest zerowana dla bezpieczeństwa.
 * 
 * @param req_n Żądany rozmiar macierzy (n x n).
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
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

/**
 * @brief Wstawia wartość w określone miejsce macierzy.
 * @param x Indeks wiersza (0-based).
 * @param y Indeks kolumny (0-based).
 * @param wartosc Wartość do wstawienia.
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::wstaw(int x, int y, int wartosc) {
    if (x >= 0 && x < n && y >= 0 && y < n) data[x * n + y] = wartosc;
    return *this;
}

/**
 * @brief Odczytuje wartość z określonego miejsca macierzy.
 * @param x Indeks wiersza (0-based).
 * @param y Indeks kolumny (0-based).
 * @return Wartość elementu macierzy. Zwraca 0 jeśli indeksy są poza zakresem.
 */
int matrix::pokaz(int x, int y) const {
    if (x >= 0 && x < n && y >= 0 && y < n) return data[x * n + y];
    return 0;
}

/**
 * @brief Transponuje macierz (zamienia wiersze z kolumnami).
 * 
 * Po transponowaniu element macierzy znajdujący się na pozycji (i, j)
 * będzie znajduje się na pozycji (j, i).
 * 
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
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

/**
 * @brief Wypełnia macierz losowymi wartościami z zakresu [0, 9].
 * 
 * Każdy element macierzy otrzymuje losową wartość całkowitą z przedziału 0-9.
 * 
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::losuj() {
    for (int i = 0; i < n * n; ++i) data[i] = rand() % 10;
    return *this;
}

/**
 * @brief Wypełnia losowo wybrane pozycje losowymi wartościami z zakresu [0, 9].
 * 
 * Macierz jest najpierw zerowana, następnie x losowo wybranych pozycji
 * otrzymuje losowe wartości z zakresu 0-9.
 * 
 * @param x Liczba pozycji do wypełnienia losowymi wartościami.
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::losuj(int x) {
    for (int i = 0; i < n * n; ++i) data[i] = 0;
    for (int k = 0; k < x; ++k) {
        int r = rand() % n;
        int c = rand() % n;
        data[r * n + c] = rand() % 10;
    }
    return *this;
}

// --- Algorytmy ---

/**
 * @brief Wypełnia główną diagonalę macierzy wartościami z tablicy.
 * 
 * Pozostałe elementy macierzy są zerowane.
 * 
 * @param t Wskaźnik na tablicę zawierającą co najmniej n elementów.
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::diagonalna(int* t) {
    return diagonalna_k(0, t);
}

/**
 * @brief Wypełnia diagonalę przesuniętą o k pozycji wartościami z tablicy.
 * 
 * Pozostałe elementy macierzy są zerowane. Jeśli k > 0, diagonala znajduje się
 * powyżej głównej diagonali. Jeśli k < 0, diagonala znajduje się poniżej głównej diagonali.
 * 
 * @param k Przesunięcie diagonali (dodatnie - powyżej głównej, ujemne - poniżej).
 * @param t Wskaźnik na tablicę zawierającą co najmniej n elementów.
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::diagonalna_k(int k, int* t) {
    for (int i = 0; i < n * n; ++i) data[i] = 0;
    
    int idx = 0;
    for (int i = 0; i < n; ++i) {
        int j = i + k;
        if (j >= 0 && j < n) {
            data[i * n + j] = t[idx++];
        }
    }
    return *this;
}

/**
 * @brief Wypełnia określoną kolumnę macierzy wartościami z tablicy.
 * @param x Indeks kolumny (0-based).
 * @param t Wskaźnik na tablicę zawierającą co najmniej n elementów.
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::kolumna(int x, int* t) {
    if (x >= 0 && x < n) {
        for (int i = 0; i < n; ++i) data[i * n + x] = t[i];
    }
    return *this;
}

/**
 * @brief Wypełnia określony wiersz macierzy wartościami z tablicy.
 * @param y Indeks wiersza (0-based).
 * @param t Wskaźnik na tablicę zawierającą co najmniej n elementów.
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::wiersz(int y, int* t) {
    if (y >= 0 && y < n) {
        for (int i = 0; i < n; ++i) data[y * n + i] = t[i];
    }
    return *this;
}

/**
 * @brief Tworzy macierz jednostkową (1 na głównej diagonali, 0 w pozostałych miejscach).
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::przekatna() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            data[i * n + j] = (i == j) ? 1 : 0;
    return *this;
}

/**
 * @brief Tworzy macierz z jedynkami poniżej głównej diagonali, zerami w pozostałych miejscach.
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::pod_przekatna() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            data[i * n + j] = (i > j) ? 1 : 0;
    return *this;
}

/**
 * @brief Tworzy macierz z jedynkami powyżej głównej diagonali, zerami w pozostałych miejscach.
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::nad_przekatna() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            data[i * n + j] = (j > i) ? 1 : 0;
    return *this;
}

/**
 * @brief Tworzy macierz w wzór szachownicy (0 i 1 na zmianę).
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::szachownica() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            data[i * n + j] = (i + j) % 2;
    return *this;
}

// --- Operatory ---

/**
 * @brief Dodaje dwie macierze element po elemencie.
 * @param m Macierz do dodania.
 * @return Nowa macierz będąca sumą dwóch macierzy. Zwraca macierz zerową jeśli rozmiary się nie zgadzają.
 */
matrix matrix::operator+(const matrix& m) {
    matrix temp(n);
    if (n != m.n) return temp;
    for (int i = 0; i < n * n; ++i) {
        temp.data[i] = data[i] + m.data[i];
    }
    return temp;
}

/**
 * @brief Mnoży dwie macierze (mnożenie macierzowe).
 * 
 * Wynikiem jest macierz C, gdzie C[i][j] = Σ(k=0 to n-1) A[i][k] × B[k][j]
 * 
 * @param m Macierz do pomnożenia.
 * @return Nowa macierz będąca iloczynem dwóch macierzy. Zwraca macierz zerową jeśli rozmiary się nie zgadzają.
 */
matrix matrix::operator*(const matrix& m) {
    matrix temp(n);
    if (n != m.n) return temp;
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

/**
 * @brief Dodaje skalar do każdego elementu macierzy.
 * @param a Wartość skalarna do dodania.
 * @return Nowa macierz z dodanym skalarem do każdego elementu.
 */
matrix matrix::operator+(int a) {
    matrix temp(*this);
    for (int i = 0; i < n * n; ++i) temp.data[i] += a;
    return temp;
}

/**
 * @brief Mnoży każdy element macierzy przez skalar.
 * @param a Wartość skalarna do pomnożenia.
 * @return Nowa macierz z każdym elementem pomnożonym przez skalar.
 */
matrix matrix::operator*(int a) {
    matrix temp(*this);
    for (int i = 0; i < n * n; ++i) temp.data[i] *= a;
    return temp;
}

/**
 * @brief Odejmuje skalar od każdego elementu macierzy.
 * @param a Wartość skalarna do odjęcia.
 * @return Nowa macierz z odjętym skalarem od każdego elementu.
 */
matrix matrix::operator-(int a) {
    matrix temp(*this);
    for (int i = 0; i < n * n; ++i) temp.data[i] -= a;
    return temp;
}

/**
 * @brief Postinkrementacja. Zwiększa każdy element macierzy o 1.
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::operator++(int) {
    for (int i = 0; i < n * n; ++i) data[i]++;
    return *this;
}

/**
 * @brief Postdekrementacja. Zmniejsza każdy element macierzy o 1.
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::operator--(int) {
    for (int i = 0; i < n * n; ++i) data[i]--;
    return *this;
}

/**
 * @brief Dodaje skalar do macierzy, modyfikując ją na miejscu.
 * @param a Wartość skalarna do dodania.
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::operator+=(int a) {
    for (int i = 0; i < n * n; ++i) data[i] += a;
    return *this;
}

/**
 * @brief Odejmuje skalar od macierzy, modyfikując ją na miejscu.
 * @param a Wartość skalarna do odjęcia.
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::operator-=(int a) {
    for (int i = 0; i < n * n; ++i) data[i] -= a;
    return *this;
}

/**
 * @brief Mnoży macierz przez skalar, modyfikując ją na miejscu.
 * @param a Wartość skalarna do pomnożenia.
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::operator*=(int a) {
    for (int i = 0; i < n * n; ++i) data[i] *= a;
    return *this;
}

/**
 * @brief Dodaje do każdego elementu część całkowitą liczby zmiennoprzecinkowej.
 * @param val Liczba zmiennoprzecinkowa, z której pobierana jest część całkowita.
 * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
 */
matrix& matrix::operator()(double val) {
    int intPart = static_cast<int>(val);
    for (int i = 0; i < n * n; ++i) data[i] += intPart;
    return *this;
}

/**
 * @brief Porównuje dwie macierze na równość.
 * @param m Macierz do porównania.
 * @return true jeśli macierze są równe (wszystkie elementy identyczne), false w przeciwnym razie.
 */
bool matrix::operator==(const matrix& m) {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i)
        if (data[i] != m.data[i]) return false;
    return true;
}

/**
 * @brief Porównuje dwie macierze (większe niż).
 * @param m Macierz do porównania.
 * @return true jeśli wszystkie elementy bieżącej macierzy są większe od odpowiadających elementów macierzy m.
 */
bool matrix::operator>(const matrix& m) {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i)
        if (data[i] <= m.data[i]) return false;
    return true;
}

/**
 * @brief Porównuje dwie macierze (mniejsze niż).
 * @param m Macierz do porównania.
 * @return true jeśli wszystkie elementy bieżącej macierzy są mniejsze od odpowiadających elementów macierzy m.
 */
bool matrix::operator<(const matrix& m) {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i)
        if (data[i] >= m.data[i]) return false;
    return true;
}

// --- Funkcje Zaprzyjaźnione ---

/**
 * @brief Dodaje skalar z lewej strony do macierzy (a + m).
 * @param a Wartość skalarna.
 * @param m Macierz.
 * @return Nowa macierz będąca sumą skalara i macierzy.
 */
matrix operator+(int a, matrix& m) { return m + a; }

/**
 * @brief Mnoży skalar z lewej strony przez macierz (a * m).
 * @param a Wartość skalarna.
 * @param m Macierz.
 * @return Nowa macierz będąca iloczynem skalara i macierzy.
 */
matrix operator*(int a, matrix& m) { return m * a; }

/**
 * @brief Odejmuje macierz od skalara (a - m).
 * @param a Wartość skalarna.
 * @param m Macierz.
 * @return Nowa macierz będąca różnicą skalara i macierzy.
 */
matrix operator-(int a, matrix& m) {
    matrix temp(m.n);
    for (int i = 0; i < m.n * m.n; ++i) temp.data[i] = a - m.data[i];
    return temp;
}

/**
 * @brief Wypisuje macierz do strumienia wyjścia w formacie tabelarycznym.
 * 
 * Macierz wyświetlana jest w formacie tabelarycznym z pionowymi kreskami ograniczającymi,
 * elementy wyrównane do prawej z szerokością 3 znaków.
 * 
 * @param o Strumień wyjścia.
 * @param m Macierz do wypisania.
 * @return Referencja do strumienia wyjścia.
 */
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
