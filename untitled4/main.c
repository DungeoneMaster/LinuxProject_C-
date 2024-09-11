#define K 10

#include <stdio.h>
#include <stdlib.h>

struct Student{
    int id;
    int price[K];
    float medium_price;

};
struct BunchStudents{
    struct Student *student;
    int size_bunch;
    float medium_price;
};
struct Tree{

    struct BunchStudents bunch_students;
    struct Tree *left;
    struct Tree *right;
};
struct DataChange{
    int id;
    int number_object;
    int changed_price;
};

void BH(struct BunchStudents *bunch_students,struct Student student)
{

    if(bunch_students->student == NULL) {
        bunch_students->size_bunch = 1;
        bunch_students->medium_price = student.medium_price;
        bunch_students->student = (struct Student *) malloc(sizeof(struct Student));
        bunch_students->student[0] = student;
    }
    else{
        int *size = &bunch_students->size_bunch;
        *size += 1;
        bunch_students->student = (struct Student*) realloc(bunch_students->student,(*size)*sizeof(struct Student));
        bunch_students->student[(*size)-1] = student;
    }
}

//добавление узлов в дерево
struct Tree* create_node(struct Student student)
{
    struct Tree *tmp = (struct Tree*) malloc(sizeof(struct Tree));

    tmp->left = NULL;
    tmp->right = NULL;
    BH(&tmp->bunch_students,student);

    return tmp;
}

struct Tree* insert(struct Tree* tree, struct Student student)
{
    if(tree == NULL)
        return create_node(student);
    if(student.medium_price < tree->bunch_students.medium_price)
        tree->left =  insert(tree->left, student);
    else if(student.medium_price > tree->bunch_students.medium_price)
        tree->right = insert(tree->right, student);
    else
        BH(&tree->bunch_students, student);
    return tree;
}

//освобождение динамической памяти в дереве
void delete_tree(struct Tree *tree)
{
    if(tree != NULL) {

        delete_tree(tree->right);
        delete_tree(tree->left);
        tree->bunch_students.student = NULL;
        tree->bunch_students.size_bunch = 0;
        tree->bunch_students.medium_price = 0;
        tree = NULL;
    }
}




float get_medium_price(int list_price[K])
{
    int count = 0;
    for(int i = 0; i < K; i++)
        count += list_price[i];
    return (float)count / K;
}

void change_price(struct Student *students,int size,struct DataChange data_change)
{
    for(int i = 0;i < size; i++){
        if(students[i].id == data_change.id){
            students[i].price[data_change.number_object-1] = data_change.changed_price;
            students[i].medium_price = get_medium_price(students[i].price);
            break;
        }
    }
}

void find_sheet(struct Tree *tree,float border_price)
{

    //float left = tree->left->bunch_students.medium_price;
    //float right = tree->right->bunch_students.medium_price;


    if(tree->left != NULL)
        find_sheet(tree->left,border_price);
    if(tree->right != NULL)
        find_sheet(tree->right,border_price);
    if(tree->bunch_students.medium_price < border_price)
        delete_tree(tree);

}



void count_student_border(struct Tree* tree, float border, int *m) {

    if(tree->right != NULL)
        count_student_border(tree->right, border, m);
    if(tree->left != NULL)
        count_student_border(tree->left, border, m);
    if(tree->bunch_students.medium_price >= border)
        *m += tree->bunch_students.size_bunch;

}




int char_f (char str[10], char t)
{
    if(str[0] == t)
        return 1;
    return 0;
}

int main()
{

    struct Tree *root = NULL;
    struct Student *students;


    char buffer[10];
    FILE *file = fopen("input.txt","r");


    int k = 1;

    while(char_f(fgets(buffer,sizeof(buffer),file), 'C') == 0){

        students = (struct Student*) realloc(students,k*sizeof(struct Student));



        fscanf(file, "%d",&students[k-1].id);

        for(int i = 0; i < K; i++)
            fscanf(file, "%i",&students[k-1].price[i]);
        students[k-1].medium_price = get_medium_price(students[k-1].price);

        k++;

    }
    int tt = 1;
    while(tt == 1 || char_f(fgets(buffer,sizeof(buffer),file), 'B') == 0){
        struct DataChange data_change;
        fscanf(file,"%d",&data_change.id);
        fscanf(file,"%d",&data_change.number_object);
        fscanf(file,"%d",&data_change.changed_price);

        change_price(students,k,data_change);
        tt = 2;
    }
    for(int i = 0; i < k-2;i++)
        root = insert(root,students[i]);

    float border_price;
    float border_price_super;
    fscanf(file,"%f",&border_price);
    fscanf(file,"%f",&border_price_super);
    int count_live_student=0;
    int count_super_student=0;

    find_sheet(root,border_price);
    count_student_border(root,border_price, &count_live_student);
    printf("%d ",count_live_student);
    count_student_border(root,border_price_super, &count_super_student);
    printf("%d",count_super_student);


    //+++//множество чуваков со средним баллом (структура) для бинарного дерева
    //+++//обработка пересдачи => обновление данных чуваков

    //+++//сортирвка бинарного дерева
    //удаление ветви, начиная с какоготоо ключа

    //счет чуваков по баллам с учетом покинувших + крутых чуваков
    //ввод данных





/*
    int i = 4;

    while(i < 3) {
        students = (struct Student *) realloc(students, (i + 1) * sizeof(struct Student));
        scanf("%d",&students[i].id);
        for(int j = 0;  j < K; j++)
            scanf("%d",&students[i].price[j]);

        students[i].medium_price = get_medium_price(students[i].price);
        i++;

    }
    */


    //stree(&newTree, &tree,3.9);

    free(students);

    delete_tree(root);


}