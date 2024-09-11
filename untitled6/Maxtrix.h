//
// Created by dno on 08.09.2024.
//

#ifndef UNTITLED6_MAXTRIX_H
#define UNTITLED6_MAXTRIX_H
#include <iostream>
#include <vector>
#include <memory>
using namespace std;



class Matrix;

class Matrix{

    int _size;
    vector<vector<int>> _matrix, _matrix_transpose;

    vector<int> erase(vector<int> vector, int n_elem);

public:
    Matrix(int size = 0, int k = 1);
    Matrix(int size, vector<int> array);
    Matrix(int size, vector<vector<int>> array2D);
    Matrix(const Matrix &matrix,int line, int coll);

    void input(int size);
    void output();
    void transpose(){
        for(int i = 0; i < _size; i++)
            for(int j = 0; j < _size && i != j;j++)
                _matrix_transposep[i][j] = _matrix[]
                swap(_matrix[i][j],_matrix[j][i]);
    }

    vector<int> &getM(Matrix &m,int col);

    Matrix operator () (int row, int col);
    Matrix operator + (const Matrix& matrix) ;
    Matrix operator - (const Matrix& matrix) ;
    Matrix operator * (const Matrix& matrix);
    Matrix operator ~ ();


    bool operator == (const Matrix& matrix);

    vector<int> &operator () (int col);
    vector<int> &operator [] (int row);


};




#endif //UNTITLED6_MAXTRIX_H


