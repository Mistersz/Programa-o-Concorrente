#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[]) {
    
    srand(time(NULL));
    int tamanho;
    int intervalo;
    int i;
    tamanho = atol(argv[1]);
    intervalo = atol(argv[2]);

    printf("%d ", tamanho);
 
    for(i=0;i<tamanho;i++){

        float r = rand() % intervalo+1;
        printf("%.2lf ",r);
    }

    return 0;
}
