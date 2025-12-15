#include "matrix.h"
#include <iostream>
#include <ctime>

using namespace std;

int main() {
    srand(time(NULL));

    //Test 1 Alokacja i losowanie (n=5)
    cout << "Test 1: Alokacja i losowanie (n=5)" << endl;
    matrix A(5);
    A.losuj();
    cout << "Pierwsza macierz " << A << endl;
    
    return 0;
}