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

     std::cout << "--- Test 4: Operatory arytmetyczne ---" << std::endl;
    matrix C(3); C.losuj();
    matrix D(3); D.losuj();
    std::cout << "C:\n" << C << "D:\n" << D;
    
    matrix E = C + D;
    std::cout << "C + D:\n" << E << std::endl;
    
    matrix F = C * D;
    std::cout << "C * D:\n" << F << std::endl;

    std::cout << "--- Test 5: Operator() (double) ---" << std::endl;
    C(5.99); // Powinno dodac 5
    std::cout << "C + 5:\n" << C << std::endl;

    return 0;
}