#include<stdio.h>


void troca(int *x, int *y){
    int antigoX = *x;
    *x = *y;
    *y = antigoX;
}

int main(){
    int x,y;
    scanf("%d %d", &x, &y);


    troca(&x,&y);

    printf("%d %d",x,y);


    return 0;
}