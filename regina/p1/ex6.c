#include <stdio.h>


int soma (int v[], int n){
    if(n == 0) return v[0];

    return v[n] + soma(v,n-1);
}

int main(){
    int n,  v[100];

    scanf("%d", &n);

    for(int i=0; i < 100; i++) scanf("%d", &v[i]);

    printf("%d\n",soma(v,n));
    return 0;
}