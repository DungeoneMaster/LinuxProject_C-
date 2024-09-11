#define K 10
#define SIZE_STUD 100

#include <stdio.h>
#include <stdlib.h>

struct Student{
    int id;
    int price[K];
    float medium_price;

};
struct List{
    struct Student student;
    struct List *next;
};
struct BunchStudents{
    struct List *list;
    int size_bunch;
    float medium_price;
};
struct Tree{

    struct BunchStudents bunch_students;
    struct Tree *left;
    struct Tree *right;
};
struct DataChange{
    int debug_id;
    int changed_price[K];
};

float get_medium_price(int array_price[K]){
    int count = 0;
    for(int i = 0; i < K; i++)
        count += array_price[i];
    return (float)count / K;
}

void create_list(struct List **head, struct Student student){
    if(head == NULL)
        return;
    *head = (struct List*)malloc(sizeof(struct List));
    (*head)->next = NULL;
    (*head)->student = student;
}

void insert_list(struct List *head, int index, struct Student student){
    if(head == NULL)
        return;
    struct List *element = NULL;
    struct List *q = head;
    int index_head = 1;
    element = (struct List*) malloc(sizeof(struct List));
    element->next = NULL;
    element->student = student;
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

void create_bunch_students(struct BunchStudents *bunch_students,struct Student student){
    create_list(&bunch_students->list,student);
    bunch_students->medium_price = student.medium_price;
    bunch_students->size_bunch = 1;
}

void delete_element(struct List **head, int index){
    struct List *q = NULL;
    struct List *to_del = NULL;
    int index_head = 0;
    if(head == NULL)
        return;
    if(*head == NULL)
        return;
    q = *head;
    if(index == 0){
        *head = (*head)->next;
        free(q);
        return;
    }
    to_del = (*head)->next;
    while((to_del->next != NULL) && (index_head < index)){
        index_head++;
        q = q->next;
        to_del = to_del->next;
    }
    q->next = to_del->next;
    free(to_del);
}

int return_index(struct List *head, int id){
    struct List *q = NULL;
    int index_head = 0;
    q = head;
    while(q->next != NULL && q->student.id != id){
        index_head++;
        q = q->next;
    }
    return index_head;
}

void update_bunch_student(struct BunchStudents *bunch_students,struct Student student){
    bunch_students->size_bunch += 1;
    insert_list(bunch_students->list,bunch_students->size_bunch-1,student);
}

struct Tree* create_node(struct Student student){
    struct Tree *tmp = (struct Tree*) malloc(sizeof(struct Tree));
    tmp->left = NULL;
    tmp->right = NULL;
    create_bunch_students(&tmp->bunch_students,student);
    return tmp;
}

struct Tree* insert(struct Tree* tree, struct Student student){
    if(tree == NULL)
        return create_node(student);
    if(student.medium_price < tree->bunch_students.medium_price)
        tree->left =  insert(tree->left, student);
    else if(student.medium_price > tree->bunch_students.medium_price)
        tree->right = insert(tree->right, student);
    else
        update_bunch_student(&tree->bunch_students, student);
    return tree;
}

void delete_tree(struct Tree *tree){
    if(tree != NULL) {
        delete_tree(tree->right);
        delete_tree(tree->left);
        delete_list(&tree->bunch_students.list);
        tree->bunch_students.size_bunch = 0;
        tree->bunch_students.medium_price = 0;
        tree = NULL;
    }
}

struct BunchStudents find_need_element(struct Tree *tree){
    if(tree->right != NULL)
        find_need_element(tree->right);
    else if(tree->left != NULL)
        find_need_element(tree->left);
    else {
        struct BunchStudents tmp = tree->bunch_students;
        delete_tree(tree);
        tree = NULL;
        return tmp;
    }
}

struct Tree* delete_element_tree(struct Tree *tree){
    if(tree == NULL)
        return NULL;
    if(tree->right == NULL && tree->left == NULL) {
        delete_tree(tree);
        return tree;
    }
    else if(tree->right == NULL)
        return tree->left;
    else if(tree->left == NULL)
        return tree->right;
    else{
        tree->bunch_students = find_need_element(tree);
        return tree;
    }
}

struct Tree* delete_null_element(struct Tree *tree){
    if(tree->bunch_students.size_bunch == 0)
        return delete_element_tree(tree);
    if(tree->left != NULL)
        delete_null_element(tree->left);
    if(tree->right != NULL)
        delete_null_element(tree->right);
    return tree;
}

void update_data_student(struct Student *student, int change_price[K]){
    for(int i = 0; i < K; i++)
        if(change_price[i] != 0)
            student->price[i] = change_price[i];
    student->medium_price = get_medium_price(student->price);
}

void change_student(struct Tree *tree, struct Student *student, int change_price[K], float old_medium_price){
    if(tree == NULL)
        return;
    struct BunchStudents *left = &tree->left->bunch_students;
    struct BunchStudents *right = &tree->right->bunch_students;
    float key = tree->bunch_students.medium_price;

    if(left != NULL && old_medium_price < key)
        change_student(tree->left, student, change_price, old_medium_price);
    if(right != NULL && old_medium_price > key)
        change_student(tree->right, student, change_price, old_medium_price);
    if(student->medium_price == key) {
        struct List **lst = &tree->bunch_students.list;
        int index = return_index(*lst,student->id);
        update_data_student(student, change_price);
        delete_element(lst, index);
        tree->bunch_students.size_bunch -= 1;
    }

}

int char_f (char str[10], char t){
    if(str[0] == t)
        return 1;
    return 0;
}

int get_debug_id(struct Student students[SIZE_STUD], int id){
    for(int i = 0;i<SIZE_STUD;i++)
        if(students[i].id == id)
            return i;
}

void find_sheet(struct Tree *tree,float border_price)
{
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

int main(){
    struct Tree *root = NULL;
    struct Student students[SIZE_STUD] = {};
    char buffer[10];
    FILE *file = fopen("input.txt","r");
    int k = 0;
    while(char_f(fgets(buffer,sizeof(buffer),file), 'C') == 0){
        fscanf(file, "%d",&students[k].id);
        for(int i = 0; i < K; i++)
            fscanf(file, "%i",&students[k].price[i]);
        students[k].medium_price = get_medium_price(students[k].price);
        k++;
    }
    for(int i = 0; i < k - 1;i++)
        root = insert(root,students[i]);
    struct DataChange data_change[SIZE_STUD];
    for(int i = 0; i < SIZE_STUD; i++) {
        for (int j = 0; j < K; j++)
            data_change[i].changed_price[j] = 0;
        data_change[i].debug_id = -1;
    }
    int tt = 0;
    int i_price;
    int price;
    int id;
    while(tt == 0 || char_f(fgets(buffer,sizeof(buffer),file), 'B') == 0){
        fscanf(file,"%d",&id);
        fscanf(file,"%d",&i_price);
        fscanf(file,"%d",&price);
        int i = get_debug_id(students,id);
        data_change[i].changed_price[i_price] = price;
        data_change[i].debug_id = i;
        tt++;
    }
    for(int i = 0; i < SIZE_STUD; i++) {
        int j = data_change[i].debug_id;
        if(j != -1) {
            change_student(root, &students[j], data_change[i].changed_price, students[j].medium_price);
            root = insert(root,students[j]);
        }
    }
    float border_price;
    float border_price_super;
    fscanf(file,"%f",&border_price);
    fscanf(file,"%f",&border_price_super);
    int count_live_student=0;
    int count_super_student=0;

    root = delete_null_element(root);
    count_student_border(root,border_price, &count_live_student);
    printf("%d ",count_live_student);
    count_student_border(root,border_price_super, &count_super_student);
    printf("%d",count_super_student);

}