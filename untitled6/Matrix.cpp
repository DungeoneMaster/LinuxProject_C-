//
// Created by dno on 08.09.2024.
//
#include "Maxtrix.h"

vector<int> Matrix::erase(vector<int> vec, int n_elem) {
    vector<int> temp(_size-1);
    for(int i = 0; i < _size; i++){
        if(i >= n_elem)
            temp[i] = vec[i+1];
        else
            temp[i] = vec[i];
    }
    return temp;
}

Matrix::Matrix(int size, int k): _size(size),_matrix(size,vector<int>(size)) {
    if(k != 0)
        for(int i = 0; i < size; i++)
            _matrix[i][i] = k;
}
Matrix::Matrix(int size, vector<int> array) : Matrix{size, 0} {
    for(int i = 0; i < size;i++)
        _matrix[i][i] = array[i];
};
Matrix::Matrix(int size, vector<vector<int>> array2D) : Matrix{size, 0} {
    for(int i = 0; i < size;i++)
        for(int j = 0; j < size;j++)
            _matrix[i][j] = array2D[i][j];
};

void Matrix::input(int size){
    _size = size;
    vector<vector<int>> array2D(size,vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            cin >> array2D[i][j];
    _matrix = array2D;
}
void Matrix::output() {
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++)
            cout << _matrix[i][j] << " ";
        cout << "\n";
    }
}

Matrix Matrix::operator () (int row, int col) {
    int temp_s= _size - 1;
    vector<vector<int>> matrix(temp_s,vector<int>(temp_s));
    for(int i = 0; i < temp_s;i++){
        if(i > row - 1)
            matrix[i] = erase(_matrix[i+1],col);
        else
            matrix[i] = erase(_matrix[i],col);
    }
    return Matrix(temp_s,matrix);
}

//void Matrix::change(vector<int> vec){
//    for(int i = 0; i < _size; i++)
//        _matrix[i] = vec;
//}



vector<int> &Matrix::operator [] (int row){
    row--;
    return _matrix[row];
}
vector<int> &Matrix::operator () (int col){
    col--;
    vector<int> vec(_size);
    for(int j = 0; j < col; j++)
        vec[j] = _matrix[j][col];
    return vec;
}


Matrix Matrix::operator + (const Matrix& matrix) {
    for(int i = 0; i < _size;i++)
        for(int j = 0; j < _size;j++)
            _matrix[i][j] += matrix._matrix[i][j];
    return Matrix{_size,_matrix};
}
Matrix Matrix::operator - (const Matrix& matrix) {
    for(int i = 0; i < _size;i++)
        for(int j = 0; j < _size;j++)
            _matrix[i][j] -= matrix._matrix[i][j];
    return Matrix{_size,_matrix};
}
Matrix Matrix::operator * (const Matrix& matrix) {
    vector<vector<int>> array2D(_size,vector<int>(_size));
    for(int i = 0; i < _size;i++) {
        for (int j = 0; j < _size; j++) {
            int result = 0;
            for(int g = 0; g < _size; g++)
                result += _matrix[i][g] * matrix._matrix[g][j];
            array2D[i][j] = result;
        }
    }
    return Matrix{_size,array2D};
}
Matrix Matrix::operator ~ (){
    for(int i = 0; i < _size; i++)
        for(int j = 0; j < _size && i != j;j++)
            swap(_matrix[i][j],_matrix[j][i]);
    return Matrix{_size,_matrix};
}


bool Matrix::operator == (const Matrix& matrix) {
    for(int i = 0; i < _size;i++)
        for (int j = 0; j < _size; j++)
            if(_matrix[i][j] != matrix._matrix[i][j])
                return false;
    return true;
}


