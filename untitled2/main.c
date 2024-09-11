#include <stdio.h>
#include <stdlib.h>



struct DateTime{
    int year , month , day ;
    int hours , minutes , seconds ;
};


}

int main(){
    int n, min_year = 7000, min_month = 20, min_day = 40, min_hour = 30, min_minute = 70, min_seconds = 70;
    scanf("%d",&n);
    struct DateTime *date_time = (struct DateTime*)malloc(sizeof(struct DateTime)*n);



    free(date_time);
}












/*int main()
{
    int a[100][100],n,m;

    scanf("%d %d",&n, &m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d",&a[i][j]);
    int c = 0, mm = 0;
    for (int i = 0; i < n; i++) {

        for(int j = 0; j < m;j++){

            if (a[i][j] != 0){
                c += 1;
                mm = 1;
            }
            else if(c > 0 ){
                printf("%d ",c);
                c=0;
            }

            if(c > 0 && j == m-1) {
                printf("%d ", c);
                c = 0;
                break;
            }
            if(mm == 0 &&  j == m-1)
                printf("%c", '\0');
        }
        mm = 0;

        printf("\n");
    }
    for (int i = 0; i < m; i++) {

        for(int j = 0; j < n;j++){

            if (a[j][i] != 0){
                c += 1;
                mm = 1;
            }
            else if(c > 0 ){
                printf("%d ",c);
                c=0;
            }

            if(c > 0 && j == m-1) {
                printf("%d ", c);
                c = 0;
                break;
            }
            if(mm == 0 &&  j == m-1)
                printf("%c", '');
        }
        mm = 0;
        printf("\n");
    }



    return 0;
}*/