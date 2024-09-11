#define SIZE_MATRIX 64
#define SIZE_ARRAY_3D 100

#include <stdio.h>

struct ArrayMatrix{
    int det;
    int size_matrix;
    int matrix[SIZE_MATRIX][SIZE_MATRIX];
};

void swap(struct ArrayMatrix *a, struct ArrayMatrix *b)
{
    struct ArrayMatrix temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct ArrayMatrix arr[], int low, int high)
{
    int pivot = arr[low].det;
    int i = low;
    int j = high;

    while (i < j) {
        while (arr[i].det <= pivot && i <= high - 1)
            i++;
        while (arr[j].det > pivot && j >= low + 1)
            j--;
        if (i < j)
            swap(&arr[i], &arr[j]);
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void quick_sort(struct ArrayMatrix array_struct[], int low, int high)
{
    if (low < high) {
        int partitionIndex = partition(array_struct, low, high);
        quick_sort(array_struct, low, partitionIndex - 1);
        quick_sort(array_struct, partitionIndex + 1, high);
    }
}

int pow4(int degree)
{
    return degree % 2 ? -1 : 1;
}

int determinant(int matrix[SIZE_MATRIX][SIZE_MATRIX], int n)
{
    int det = 0;
    if (n == 1)
        return matrix[0][0];
    else if (n == 2) {
        det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
        return det;
    }
    else {
        int temp_matrix[SIZE_MATRIX][SIZE_MATRIX];
        for (int p = 0; p < n; p++) {
            int h = 0, k = 0;
            for (int i = 1; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (j == p)
                        continue;
                    temp_matrix[h][k] = matrix[i][j];
                    k++;
                    if (k == n - 1) {
                        h++;
                        k = 0;
                    }
                }
            }
            det = det + matrix[0][p] * pow4(p) * determinant(temp_matrix, n - 1);
        }
        return det;
    }
}

int det_thought_linear_dependence(int matrix[SIZE_MATRIX][SIZE_MATRIX], int n)
{
    for(int k = 0; k < n-1; k++){
        for(int i = k+1; i < n; i++){
            double temp = matrix[i][0];
            if(temp == 0)
                break;
            for(int j = 1; j < n; j++){
                double tmp;
                if (matrix[k][j] != 0)
                    tmp = (double)(matrix[i][j] * matrix[k][0]) / matrix[k][j];
                else
                    break;
                if(tmp == temp){
                    if(j != n-1)
                        continue;
                    else
                        return 0;
                }
                break;
            }
        }
    }
    return determinant(matrix,n);
}

int main()
{
    struct ArrayMatrix array_matrix[SIZE_ARRAY_3D];

    int size3D;
    int size_matrix;

    FILE *file = fopen("input.txt","r");
    fscanf(file,"%i",&size3D);

    for(int k = 0; k < size3D; k++) {

        fscanf(file,"%i",&size_matrix);
        array_matrix[k].size_matrix = size_matrix;

        for(int i =0;i<size_matrix;i++)
            for(int j =0;j<size_matrix;j++)
                fscanf(file, "%i", &array_matrix[k].matrix[i][j]);

        array_matrix[k].det = det_thought_linear_dependence(array_matrix[k].matrix, size_matrix);

    }
    quick_sort(array_matrix, 0, size3D - 1);

    for(int k = 0; k < size3D; k++) {
        int s = array_matrix[k].size_matrix;
        for(int i = 0; i < s;i++){
            for(int j = 0; j < s;j++)
                printf("%d ", array_matrix[k].matrix[i][j]);
            printf("\n");
        }
    }
    fclose(file);
    return 0;
}