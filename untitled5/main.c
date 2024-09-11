#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define sdf char
#define test(a) \
a sum_##a(a val1, a val2){ \
return val1 + val2;        \
}


test(char);
test(int);

#define n 10

int max(int* A, size_t len){
    int max = 0;
    for (int i = 0; i < len; ++i) {
        if(max < A[i]) max = A[i];
    }
    return max;
}

int max_var(int A[], int var_arr[], int len, int elem){
    int max_elem = 0;
    for (int i = 0; i < len; ++i) {
        if (var_arr[i] >= max_elem && A[n-i] >= elem){
            max_elem = var_arr[i];
        }
    }
    return max_elem;
}

int longest_subseq(int A[]){
    int arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = 0;
    }
    for (int i = n-1; i >= 0; --i) {
        arr[i] = 1 + max_var(A, arr,n-i,A[i]);
    }
    return max(arr, n);
}

int main() {
    int arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = i;
    }
    printf("%d", longest_subseq(arr));
}
