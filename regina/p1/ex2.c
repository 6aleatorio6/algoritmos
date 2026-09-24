#include<stdio.h>
#include<stdio.h>
#include<math.h>


int main(){
    double  termo =1, soma = 1,x =0 ;

    scanf("%lf", &x);


    // isso causava erro
    // soma += x;

    for(int n =1; fabs(termo) >= 0.001; n++){
        termo = termo * x/n;

        soma += termo; 
    }


    printf("e^%.2f = %.3f\n", x, soma);
    return  0;

}