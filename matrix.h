#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <memory>
#include <iomanip>

/**
 * @class matrix
 * @brief Klasa reprezentująca macierz kwadratową n×n z dynamicznym zarządzaniem pamięcią.
 * 
 * Klasa matrix udostępnia operacje na macierzach kwadratowych, w tym:
 * - zarządzanie pamięcią za pomocą inteligentnych wskaźników,
 * - operacje arytmetyczne (dodawanie, mnożenie),
 * - algorytmy wypełniania (diagonalna, szachownica itp.),
 * - operatory porównania i modyfikujące.
 */
class matrix {
private:
    std::unique_ptr<int[]> data; ///< Inteligentny wskaźnik do tablicy elementów macierzy
    int n;                       ///< Aktualny rozmiar logiczny macierzy (n x n)
    int allocated_n;             ///< Rozmiar fizycznie zaalokowanej pamięci

public:
    // --- Konstruktory i Destruktor ---
    
    /**
     * @brief Domyślny konstruktor. Inicjalizuje macierz o rozmiarze 0.
     */
    matrix();
    
    /**
     * @brief Konstruktor z parametrem rozmiaru.
     * @param n Rozmiar macierzy (n x n). Jeśli n ≤ 0, macierz pozostaje pusta.
     */
    matrix(int n);
    
    /**
     * @brief Konstruktor inicjujący macierz wartościami z tablicy.
     * @param n Rozmiar macierzy (n x n).
     * @param t Wskaźnik na tablicę zawierającą n² elementów w porządku wiersz po wierszu.
     */
    matrix(int n, int* t);
    
    /**
     * @brief Konstruktor kopiujący. Wykonuje głęboką kopię danych macierzy.
     * @param m Macierz do skopiowania.
     */
    matrix(const matrix& m);
    
    /**
     * @brief Destruktor. Automatycznie zwalnia dynamicznie przydzieloną pamięć.
     */
    ~matrix();

    // --- Zarządzanie pamięcią ---
    
    /**
     * @brief Alokuje lub realokuje pamięć dla macierzy o zadanym rozmiarze.
     * @param n Żądany rozmiar macierzy (n x n).
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& alokuj(int n);

    // --- Metody operacyjne ---
    
    /**
     * @brief Wstawia wartość w określone miejsce macierzy.
     * @param x Indeks wiersza (0-based).
     * @param y Indeks kolumny (0-based).
     * @param wartosc Wartość do wstawienia.
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& wstaw(int x, int y, int wartosc);
    
    /**
     * @brief Odczytuje wartość z określonego miejsca macierzy.
     * @param x Indeks wiersza (0-based).
     * @param y Indeks kolumny (0-based).
     * @return Wartość elementu macierzy. Zwraca 0 jeśli indeksy są poza zakresem.
     */
    int pokaz(int x, int y) const;
    
    /**
     * @brief Transponuje macierz (zamienia wiersze z kolumnami).
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& dowroc();
    
    /**
     * @brief Wypełnia macierz losowymi wartościami z zakresu [0, 9].
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& losuj();
    
    /**
     * @brief Wypełnia losowo wybrane pozycje losowymi wartościami z zakresu [0, 9].
     * @param x Liczba pozycji do wypełnienia losowymi wartościami.
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& losuj(int x);

    // --- Algorytmy wypełniania ---
    
    /**
     * @brief Wypełnia główną diagonalę macierzy wartościami z tablicy.
     * @param t Wskaźnik na tablicę zawierającą co najmniej n elementów.
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& diagonalna(int* t);
    
    /**
     * @brief Wypełnia diagonalę przesuniętą o k pozycji wartościami z tablicy.
     * @param k Przesunięcie diagonali (dodatnie - powyżej głównej, ujemne - poniżej).
     * @param t Wskaźnik na tablicę zawierającą co najmniej n elementów.
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& diagonalna_k(int k, int* t);
    
    /**
     * @brief Wypełnia określoną kolumnę macierzy wartościami z tablicy.
     * @param x Indeks kolumny (0-based).
     * @param t Wskaźnik na tablicę zawierającą co najmniej n elementów.
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& kolumna(int x, int* t);
    
    /**
     * @brief Wypełnia określony wiersz macierzy wartościami z tablicy.
     * @param y Indeks wiersza (0-based).
     * @param t Wskaźnik na tablicę zawierającą co najmniej n elementów.
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& wiersz(int y, int* t);
    
    /**
     * @brief Tworzy macierz jednostkową (1 na głównej diagonali, 0 w pozostałych miejscach).
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& przekatna();
    
    /**
     * @brief Tworzy macierz z jedynkami poniżej głównej diagonali.
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& pod_przekatna();
    
    /**
     * @brief Tworzy macierz z jedynkami powyżej głównej diagonali.
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& nad_przekatna();
    
    /**
     * @brief Tworzy macierz w wzór szachownicy (0 i 1).
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& szachownica();

    // --- Operatory Arytmetyczne ---
    
    /**
     * @brief Dodaje dwie macierze element po elemencie.
     * @param m Macierz do dodania.
     * @return Nowa macierz będąca sumą dwóch macierzy. Zwraca macierz zerową jeśli rozmiary się nie zgadzają.
     */
    matrix operator+(const matrix& m);
    
    /**
     * @brief Mnoży dwie macierze (mnożenie macierzowe).
     * @param m Macierz do pomnożenia.
     * @return Nowa macierz będąca iloczynem dwóch macierzy. Zwraca macierz zerową jeśli rozmiary się nie zgadzają.
     */
    matrix operator*(const matrix& m);
    
    /**
     * @brief Dodaje skalar do każdego elementu macierzy.
     * @param a Wartość skalarna do dodania.
     * @return Nowa macierz z dodanym skalarem do każdego elementu.
     */
    matrix operator+(int a);
    
    /**
     * @brief Mnoży każdy element macierzy przez skalar.
     * @param a Wartość skalarna do pomnożenia.
     * @return Nowa macierz z każdym elementem pomnożonym przez skalar.
     */
    matrix operator*(int a);
    
    /**
     * @brief Odejmuje skalar od każdego elementu macierzy.
     * @param a Wartość skalarna do odjęcia.
     * @return Nowa macierz z odjętym skalarem od każdego elementu.
     */
    matrix operator-(int a);

    // --- Operatory Modyfikujące ---
    
    /**
     * @brief Postinkrementacja. Zwiększa każdy element macierzy o 1.
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& operator++(int);
    
    /**
     * @brief Postdekrementacja. Zmniejsza każdy element macierzy o 1.
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& operator--(int);
    
    /**
     * @brief Dodaje skalar do macierzy, modyfikując ją na miejscu.
     * @param a Wartość skalarna do dodania.
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& operator+=(int a);
    
    /**
     * @brief Odejmuje skalar od macierzy, modyfikując ją na miejscu.
     * @param a Wartość skalarna do odjęcia.
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& operator-=(int a);
    
    /**
     * @brief Mnoży macierz przez skalar, modyfikując ją na miejscu.
     * @param a Wartość skalarna do pomnożenia.
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& operator*=(int a);
    
    /**
     * @brief Dodaje do każdego elementu część całkowitą liczby zmiennoprzecinkowej.
     * @param val Liczba zmiennoprzecinkowa, z której pobierana jest część całkowita.
     * @return Referencja do bieżącego obiektu umożliwiająca łańcuchowanie operacji.
     */
    matrix& operator()(double val);

    // --- Operatory Porównania ---
    
    /**
     * @brief Porównuje dwie macierze na równość.
     * @param m Macierz do porównania.
     * @return true jeśli macierze są równe (wszystkie elementy identyczne), false w przeciwnym razie.
     */
    bool operator==(const matrix& m);
    
    /**
     * @brief Porównuje dwie macierze (większe niż).
     * @param m Macierz do porównania.
     * @return true jeśli wszystkie elementy bieżącej macierzy są większe od odpowiadających elementów macierzy m.
     */
    bool operator>(const matrix& m);
    
    /**
     * @brief Porównuje dwie macierze (mniejsze niż).
     * @param m Macierz do porównania.
     * @return true jeśli wszystkie elementy bieżącej macierzy są mniejsze od odpowiadających elementów macierzy m.
     */
    bool operator<(const matrix& m);

    // --- Funkcje Zaprzyjaźnione ---
    
    /**
     * @brief Dodaje skalar z lewej strony do macierzy (a + m).
     * @param a Wartość skalarna.
     * @param m Macierz.
     * @return Nowa macierz będąca sumą skalara i macierzy.
     */
    friend matrix operator+(int a, matrix& m);
    
    /**
     * @brief Mnoży skalar z lewej strony przez macierz (a * m).
     * @param a Wartość skalarna.
     * @param m Macierz.
     * @return Nowa macierz będąca iloczynem skalara i macierzy.
     */
    friend matrix operator*(int a, matrix& m);
    
    /**
     * @brief Odejmuje macierz od skalara (a - m).
     * @param a Wartość skalarna.
     * @param m Macierz.
     * @return Nowa macierz będąca różnicą skalara i macierzy.
     */
    friend matrix operator-(int a, matrix& m);
    
    /**
     * @brief Wypisuje macierz do strumienia wyjścia w formacie tabelarycznym.
     * @param o Strumień wyjścia.
     * @param m Macierz do wypisania.
     * @return Referencja do strumienia wyjścia.
     */
    friend std::ostream& operator<<(std::ostream& o, matrix& m);
};

#endif