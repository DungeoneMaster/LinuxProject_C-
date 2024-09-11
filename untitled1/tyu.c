/*#define _CRT_SECURE_NO_WARNINGS
#define SIZE_M 64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int da(int **mas, int n){
    if(n>=1)return mas[1][1];
    else return 0;
}

int main(){
    int n = 2;

    int ma2[2][2] ={{1,2},{3,4}};



    int** mas = (int**)malloc(n*sizeof(int*));
    for(int i = 0; i < n; ++i){
        mas[i] = (int*)malloc(n*sizeof(int));
        for(int j = 0; j < n; ++j)
            mas[i][j] = i + j;
    }

    printf("%d", da((int**)ma2, 2));

    for(int i = 0; i < n; ++i){
        free(mas[i]);
    }
    free(mas);
}

/*#define _CRT_SECURE_NO_WARNINGS
#define SIZE_M 64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int Lin(int** matrix, int n)
{


    for(int i = 1; i < n; i++){


        int lambda = matrix[0][0] * matrix[i][0];
        int temp = matrix[i][0] * lambda;
        for(int j = 1; j < n; j++){
            if((lambda * matrix[i][j]) / matrix[0][j] == temp)
                continue;
            else if(j == n-1)
                return 0;
            else
                break;
        }
    }
    return 1;

}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int pow4(int *degree)
{
    return *degree % 2 ? 1 : -1;
}

// Partition function
int partition(int arr[], int low, int high)
{

    // initialize pivot to be the first element
    int pivot = arr[low];
    int i = low;
    int j = high;

    while (i < j) {

        // condition 1: find the first element greater than
        // the pivot (from starting)
        while (arr[i] <= pivot && i <= high - 1) {
            i++;
        }

        // condition 2: find the first element smaller than
        // the pivot (from last)
        while (arr[j] > pivot && j >= low + 1) {
            j--;
        }
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[low], &arr[j]);
    return j;
}

// QuickSort function
void quickSort(int arr[], int low, int high)
{
    if (low < high) {

        // call Partition function to find Partition Index
        int partitionIndex = partition(arr, low, high);

        // Recursively call quickSort() for left and right
        // half based on partition Index
        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }
}

// driver code
//int main()
//{
//						int arr[] = { 19, 17, 15, 12, 16, 18, 4, 11, 13 };
//						int n = sizeof(arr) / sizeof(arr[0]);
//
//						// printing the original array
//						printf("Original array: ");
//						for (int i = 0; i < n; i++) {
//												printf("%d ", arr[i]);
//						}
//
//						// calling quickSort() to sort the given array
//						quickSort(arr, 0, n - 1);
//
//						// printing the sorted array
//						printf("\nSorted array: ");
//						for (int i = 0; i < n; i++) {
//												printf("%d ", arr[i]);
//						}
//
//						return 0;
//}

int determ(int **a, int n) {
    int det = 0;

    if (n == 1)
        return a[0][0];
    else if (n == 2) {
        det = (a[0][0] * a[1][1] - a[0][1] * a[1][0]);
        return det;
    }
    else {
        int** temp = (int**)malloc(n * sizeof(int*));
        for (int i = 0; i < n; i++)
            temp[i] = (int*)malloc(n * sizeof(int));
        for (int p = 0; p < n; p++) {
            int h = 0, k = 0;
            for (int i = 1; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (j == p)
                        continue;

                    *(temp + h*(i-1) + k) = &a[i][j];
                    k++;
                    if (k == n - 1) {
                        h++;
                        k = 0;
                    }
                }
            }
            //det = det + a[0][p] * pow4(&p) * determ(temp, n - 1);
            for (int i = 0; i < n; i++)
                free(temp[i]);
            free(temp);
        }
        return det;
    }
}
/*void test(int** a) {

    for(int i =0;i<3;i++)
        for (int j = 0; j < 3; j++)
            printf("%d", *(a + i*3+j));
}*/

/*
int main(){

    int size_array;

    FILE* file = fopen("input.txt", "r");

    //fscanf(file, "%i", &size_array);

    int danmassiv[3][3];
    for(int i = 0;i<3;i++)
        for (int j = 0; j < 3; j++)
            danmassiv[i][j] = i+j;
    Lin(danmassiv,3);
    //int op = determ(*danmassiv, 3);


    /*strcat(buffer,"[1*(");
    strcat(buffer, pattern);
    strcat(buffer, ")]");
    strcpy(normal_pattern, get_normal_pattern(buffer));

    for (int i = 0; i < count_text; i++){
          fscanf(file, "%s", str_check);
          if (check_true_pattern_and_text(normal_pattern, str_check) == 1){
                array_count[count_ret] = i;
                count_ret++;
          }
    }
    if (count_ret != 0)
          for (int i = 0; i < count_ret; i++)
                printf("%d ", array_count[i]);
    else
          printf("none");*/

/*fclose(file);



























 #include <stdio.h>
#include <stdlib.h>

struct List{
    int data;
    struct List *next;
};

void create_list(struct List **head, int data){
    if(head == NULL)
        return;

    *head = (struct List*)malloc(sizeof(struct List));
    (*head)->next = NULL;
    (*head)->data = data;
}

void insert(struct List *head, int index, int data){
    if(head == NULL)
        return;

    struct List *element = NULL;
    struct List *q = head;

    int index_head = 1;
    element = (struct List*) malloc(sizeof(struct List));
    element->next = NULL;
    element->data = data;

    //need place
    while((q->next != NULL) && (index_head < index)){
        index_head++;
        q = q->next;
    }
    if(q->next == NULL){
        q->next = element;
        return;
    }
    element->next = q->next;
    q->next = element;
}
void print_list(struct List *head){
    struct List *list = head;
    while (list != NULL){
        printf("%d ",list->data);
        list = list->next;
    }

}
void delete_list(struct List **head){
    if(head == NULL)
        return;

    struct List *element = NULL;
    struct List *q = NULL;

    element = *head;
    while (element != NULL){
        q = element;
        element = element->next;
        free(q);
    }
    *head = NULL;

}



int main(){

    struct List *list;

    create_list(&list, 4);

    insert(list,2,20);
    insert(list,4,40);
    insert(list,3,30);
    print_list(list);


    delete_list(&list);

}

}*/