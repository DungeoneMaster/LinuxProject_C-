#include <iostream>
#include "Maxtrix.h"

using namespace std;



int main() {

    int size;
    //cin >> size;

    Matrix matrix;
    //matrix.input(size);

    Matrix a(4,15);

    a.output();
    a(2)[2] = 2;
    cout << a(2)[2];
    //for(int l = 0; l < 1; l++)
    //    matrix[l].input(size);


    //((matrix[0] + matrix[1] * ~matrix[2] + k) * ~matrix[3]).output();


    return 0;
}

