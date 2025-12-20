#include "matrix.h"
#include <iostream>

using namespace std;

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
    
}